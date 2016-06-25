#pragma once

#include "Message.h"

#include <thread>
#include <map>
#include <vector>
#include <functional>

class TcpServerThreadInfo;

class TcpServer
{
public:
	void Init();
	virtual void Run();

	static void* ClientThread(void* ptr);

protected:
	virtual bool HandleMessage(TcpServerThreadInfo* threadInfo, Message* msg);
	virtual void SendMessage(TcpServerThreadInfo* threadInfo, Message* msg);

private:
	Message* CreateMessage(const char* buffer);

	std::map<std::string, std::function<Message*(void)>> m_messages;
	std::vector<TcpServerThreadInfo*> m_clientThreads;
};
