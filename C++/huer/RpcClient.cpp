#include "RpcClient.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 4096
#define DEFAULT_PORT "8888"
#define DEFAULT_HOST "raspbian-download"

RpcClient::RpcClient()
	: m_socket(INVALID_SOCKET)
{

}

void RpcClient::Init()
{
	if (m_socket != INVALID_SOCKET)
		return;

	WSADATA wsaData;
	struct addrinfo* result = nullptr, *ptr = nullptr, hints;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(DEFAULT_HOST, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) 
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) 
	{
		// Create a SOCKET for connecting to server
		m_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (m_socket == INVALID_SOCKET) 
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return;
		}

		// Connect to server.
		iResult = connect(m_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) 
		{
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (m_socket == INVALID_SOCKET) 
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		return;
	}
}

void RpcClient::Receive()
{
	if (m_socket == INVALID_SOCKET)
		return;

	char recvbuf[DEFAULT_BUFLEN];
	auto recvbuflen = DEFAULT_BUFLEN;
	int iResult;

	//do
	{
		iResult = recv(m_socket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			printf("Bytes received: %d\n", iResult);
		}
		else if (iResult == 0)
		{
			printf("Connection closed\n");
		}
		else
		{
			printf("recv failed with error: %d\n", WSAGetLastError());
		}
	} //while (iResult  0);
}

void RpcClient::Send(const char* sendbuf)
{
	if (m_socket == INVALID_SOCKET)
		return;

	// Send an initial buffer
	auto iResult = send(m_socket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR)
	{
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return;
	}

	// shutdown the connection since no more data will be sent
	iResult = shutdown(m_socket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return;
	}
}

void RpcClient::Send(xmlrpc::message* message)
{
	message->serialize();
	Send(message->GetRawMsg().c_str());
}

void RpcClient::Close()
{
	if (m_socket == INVALID_SOCKET)
		return;

	closesocket(m_socket);
	WSACleanup();
	m_socket = INVALID_SOCKET;
}