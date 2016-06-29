#include "Network/TcpServer.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <rpc-messages/status.h>

void* get_in_addr(struct sockaddr * sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in *)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void TcpServer::Run()
{
	int status;
	struct addrinfo hints, *res;
	int listner;

	// Before using hint you have to make sure that the data structure is empty 
	memset(&hints, 0, sizeof hints);
	// Set the attribute for hint
	hints.ai_family = AF_UNSPEC; // We don't care V4 AF_INET or 6 AF_INET6
	hints.ai_socktype = SOCK_STREAM; // TCP Socket SOCK_DGRAM 
	hints.ai_flags = AI_PASSIVE;

	// Fill the res data structure and make sure that the results make sense. 
	status = getaddrinfo(NULL, "8888", &hints, &res);
	if (status != 0)
	{
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
	}

	// Create Socket and check if error occured afterwards
	listner = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (listner < 0)
	{
		fprintf(stderr, "socket error: %s\n", gai_strerror(status));
	}

	// Bind the socket to the address of my local machine and port number 
	status = bind(listner, res->ai_addr, res->ai_addrlen);
	if (status < 0)
	{
		fprintf(stderr, "bind: %s\n", gai_strerror(status));
	}

	status = listen(listner, 10);
	if (status < 0)
	{
		fprintf(stderr, "listen: %s\n", gai_strerror(status));
	}

	// Free the res linked list after we are done with it	
	freeaddrinfo(res);

	// We should wait now for a connection to accept
	struct sockaddr_storage client_addr;
	socklen_t addr_size;

	// Calculate the size of the data structure	
	addr_size = sizeof client_addr;

	printf("I am now accepting connections ...\n");

	while (1) 
	{
		// Accept a new connection and return back the socket desciptor 
		int new_conn_fd = accept(listner, (struct sockaddr*)&client_addr, &addr_size);
		if (new_conn_fd < 0)
		{
			fprintf(stderr, "accept: %s\n", gai_strerror(new_conn_fd));
			continue;
		}

		TcpServerThreadInfo* ti = new TcpServerThreadInfo{ this, new_conn_fd, client_addr };
		ti->thread = std::thread{ ClientThread, reinterpret_cast<void*>(ti) };
		m_clientThreads.push_back(ti);
	}
}

void* TcpServer::ClientThread(void* ptr)
{
	TcpServerThreadInfo* ti = reinterpret_cast<TcpServerThreadInfo*>(ptr);
	TcpServer* tcpServer = ti->instance;
	struct sockaddr_storage client_addr = ti->client_addr;

	char s[INET6_ADDRSTRLEN];

	inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *) &client_addr), s, sizeof s);
	printf("I am now connected to %s \n", s);

	xmlrpc::message* msg = nullptr;
	int networkStatus;
	{
		msg = new status(status::ID::WELCOME);
		msg->serialize();
		networkStatus = send(ti->socket, msg->GetRawMsg().c_str(), msg->GetRawMsg().length(), 0);
		delete msg;
		msg = nullptr;
	}
	bool bSocketError = false;
	if (networkStatus != -1)
	{
		char buffer[4096];
		while (true)
		{
			auto bytesRecv = recv(ti->socket, buffer, 4096, 0);
			if (bytesRecv <= 0)
			{
				std::cout << gai_strerror(ti->socket);
				bSocketError = true;
				break;
			}
			else
			{
				xmlrpc::message* message = tcpServer->CreateMessage(buffer, bytesRecv);
				message->deserialize(buffer, bytesRecv);

				bool result = tcpServer->HandleMessage(ti, message);
				delete message;

				if (!result)
					break;
			}
		}
	}
	if(!bSocketError)
	{
		msg = new status(status::ID::CLOSE);
		msg->serialize();
		networkStatus = send(ti->socket, msg->GetRawMsg().c_str(), msg->GetRawMsg().length(), 0);
		delete msg;
		msg = nullptr;
	}
	close(ti->socket);

	return nullptr;
}

void TcpServer::TransmitMessage(TcpServerThreadInfo* threadInfo, xmlrpc::message* msg)
{
	send(threadInfo->socket, msg->GetRawMsg().c_str(), msg->GetRawMsg().length(), 0);
}