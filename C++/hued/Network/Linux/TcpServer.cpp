#include "TcpServer.h"

#include <stdio.h>
#include <string.h>

#ifdef LINUX
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif // LINUX
#include <iostream>

#include "StatusMessage.h"

void* get_in_addr(struct sockaddr * sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in *)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

struct TcpServerThreadInfo
{
	TcpServerThreadInfo(TcpServer* in_pInstance, int sConn, struct sockaddr_storage in_client_addr) : instance{ in_pInstance }, conn(sConn), client_addr(in_client_addr) { }

	TcpServerThreadInfo() = delete;
	TcpServerThreadInfo(const TcpServerThreadInfo& rhs) = delete;
	TcpServerThreadInfo& operator==(const TcpServerThreadInfo& rhs) = delete;

	std::thread thread;
	TcpServer* instance;
	int conn;
	struct sockaddr_storage client_addr;
};

void TcpServer::Init()
{

}

void TcpServer::Run()
{
	// Variables for writing a server. 
	/*
	1. Getting the address data structure.
	2. Openning a new socket.
	3. Bind to the socket.
	4. Listen to the socket.
	5. Accept Connection.
	6. Receive Data.
	7. Close Connection.
	*/
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

	Message* msg = nullptr;
	int status;
	{
		msg = new StatusMessage(StatusMessage::ID::WELCOME);
		msg->Serialize();
		status = send(ti->conn, msg->GetRawMsg().c_str(), msg->GetRawMsg().length(), 0);
		delete msg;
		msg = nullptr;
	}
	bool bSocketError = false;
	if (status != -1)
	{
		char buffer[4096];
		while (true)
		{
			auto bytesRecv = recv(ti->conn, buffer, 4096, 0);
			if (bytesRecv <= 0)
			{
				std::cout << gai_strerror(ti->conn);
				bSocketError = true;
				break;
			}
			else
			{
				Message* message = tcpServer->CreateMessage(buffer);
				message->Deserialize(buffer);

				bool result = tcpServer->HandleMessage(ti, message);
				delete message;

				if (!result)
					break;
			}
		}
	}
	if(!bSocketError)
	{
		msg = new StatusMessage(StatusMessage::ID::CLOSE);
		msg->Serialize();
		status = send(ti->conn, msg->GetRawMsg().c_str(), msg->GetRawMsg().length(), 0);
		delete msg;
		msg = nullptr;
	}
	close(ti->conn);

	return nullptr;
}

bool TcpServer::HandleMessage(TcpServerThreadInfo* threadInfo, Message* msg)
{
	const StatusMessage closeMessage(StatusMessage::ID::CLOSE);
	if (msg == &closeMessage)
		return false;
}

void TcpServer::SendMessage(TcpServerThreadInfo* threadInfo, Message* msg)
{
	send(threadInfo->conn, msg->GetRawMsg().c_str(), msg->GetRawMsg().length(), 0);
}

Message* TcpServer::CreateMessage(const char* buffer)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError err = doc.Parse(buffer);
	if (err != tinyxml2::XML_SUCCESS)
	{
		return nullptr;
	}

	if (tinyxml2::XMLElement* rootElem = doc.FirstChildElement("message"))
	{
		std::string type = rootElem->Attribute("type");
		return m_messages[type]();
	}

	return nullptr;
}
