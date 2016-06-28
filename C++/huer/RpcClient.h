#pragma once

#include <WinSock2.h>

class RpcClient
{
public:
	RpcClient();

	void Init();
	void Receive();
	void Run();
private:
	SOCKET m_socket;
};