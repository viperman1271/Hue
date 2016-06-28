#pragma once

#include <WinSock2.h>

class RpcClient
{
public:
	RpcClient();

	void Init();
	void Receive();
	void Send(const char* sendbuf);
	void Close();
private:
	SOCKET m_socket;
};