#include "Network/TcpServer.h"

#include <stdio.h>
#include <string.h>
#include <iostream>

#include <rpc-messages/status.h>

void TcpServer::Init()
{

}

bool TcpServer::HandleMessage(TcpServerThreadInfo* threadInfo, xmlrpc::message* msg)
{
	const status closeMessage(status::ID::CLOSE);
	if (msg == &closeMessage)
		return false;

	return true;
}

xmlrpc::message* TcpServer::CreateMessage(const char* buffer, size_t msgSize)
{
	return nullptr;
}
