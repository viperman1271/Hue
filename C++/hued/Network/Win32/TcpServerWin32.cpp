#include "Network/TcpServer.h"

#include <stdio.h>
#include <string.h>
#include <iostream>

#undef UNICODE

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif //WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <rpc-messages/status.h>

#define DEFAULT_BUFLEN 4096
#define DEFAULT_PORT "8888"

static_assert(sizeof(SOCKET) == sizeof(long), "Socket size doesn't match expectations");

void TcpServer::Run()
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	while (1)
	{
		// Accept a new connection and return back the socket desciptor 
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket < 0)
		{
			continue;
		}

		TcpServerThreadInfo* ti = new TcpServerThreadInfo{ this, static_cast<int>(ClientSocket) };
		ti->thread = std::thread{ ClientThread, reinterpret_cast<void*>(ti) };
		m_clientThreads.push_back(ti);
	}

	// No longer need server socket
	closesocket(ListenSocket);
	WSACleanup();
}

void* TcpServer::ClientThread(void* ptr)
{
	TcpServerThreadInfo* ti = reinterpret_cast<TcpServerThreadInfo*>(ptr);
	TcpServer* tcpServer = ti->instance;
	SOCKET socket = static_cast<SOCKET>(ti->socket);

	xmlrpc::message* msg = nullptr;
	int networkStatus;
	{
		msg = new status(status::ID::WELCOME);
		msg->serialize();
		networkStatus = send(socket, msg->GetRawMsg().c_str(), msg->GetRawMsg().length(), 0);
		delete msg;
		msg = nullptr;
	}
	bool bSocketError = false;
	if (networkStatus != -1)
	{
		char buffer[4096];
		while (true)
		{
			auto bytesRecv = recv(socket, buffer, 4096, 0);
			if (bytesRecv <= 0)
			{
				std::cout << WSAGetLastError();
				bSocketError = true;
				break;
			}
			else
			{
				xmlrpc::message* message = tcpServer->CreateMessage(buffer, bytesRecv);
				if (message == nullptr)
				{
					bSocketError = true;
					break;
				}

				message->deserialize(buffer, bytesRecv);

				bool result = tcpServer->HandleMessage(ti, message);
				delete message;

				if (!result)
					break;
			}
		}
	}
	if (!bSocketError)
	{
		msg = new status(status::ID::CLOSE);
		msg->serialize();
		networkStatus = send(socket, msg->GetRawMsg().c_str(), msg->GetRawMsg().length(), 0);
		delete msg;
		msg = nullptr;
	}
	closesocket(socket);
	return nullptr;
}

void TcpServer::TransmitMessage(TcpServerThreadInfo* threadInfo, xmlrpc::message* msg)
{
	send(threadInfo->socket, msg->GetRawMsg().c_str(), msg->GetRawMsg().length(), 0);
}