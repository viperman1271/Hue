#pragma once

#include <winsock2.h>
#include <xmlrpc/message.h>

class RpcClient
{
public:
	RpcClient();

	void Init();
	void Receive();
	void Send(const char* sendbuf);
	void Send(xmlrpc::message* message);
	void Close();
private:
	SOCKET m_socket;
};