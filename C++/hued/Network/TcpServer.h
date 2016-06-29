#pragma once

#include <xmlrpc/message.h>

#include <thread>
#include <map>
#include <vector>
#include <functional>

#ifdef LINUX
#include <sys/socket.h>
#endif

class TcpServer;

struct TcpServerThreadInfo
{
	TcpServerThreadInfo(TcpServer* in_pInstance, int sConn
#ifdef LINUX 
	, struct sockaddr_storage in_client_addr
#endif //LINUX
		) 
		: instance(in_pInstance)
		, socket(sConn)
#ifdef LINUX
		, client_addr(in_client_addr)
#endif // LINUX
	{ 
	}

	TcpServerThreadInfo() = delete;
	TcpServerThreadInfo(const TcpServerThreadInfo& rhs) = delete;
	TcpServerThreadInfo& operator==(const TcpServerThreadInfo& rhs) = delete;

	std::thread thread;
	TcpServer* instance;
	int socket;
#ifdef LINUX
	struct sockaddr_storage client_addr;
#endif // LINUX
};

class TcpServer
{
public:
	void Init();
	virtual void Run();

	static void* ClientThread(void* ptr);

protected:
	virtual bool HandleMessage(TcpServerThreadInfo* threadInfo, xmlrpc::message* msg);
	virtual void TransmitMessage(TcpServerThreadInfo* threadInfo, xmlrpc::message* msg);
	virtual xmlrpc::message* CreateMessage(const char* buffer, size_t msgSize);

private:
	std::vector<TcpServerThreadInfo*> m_clientThreads;
};
