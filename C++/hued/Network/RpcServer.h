#pragma once

#include "Network/TcpServer.h"

#include <xmlrpc/message.h>
#include <xmlrpc/registry.h>

class RpcMethod;
class RpcValue;
class Daemon;

class RpcServer : public TcpServer
{
	using super = TcpServer;
public:
	RpcServer(Daemon* daemon);

	void Run() override;
	Daemon* GetDaemon() const { return m_daemon; }

protected:
	bool HandleMessage(TcpServerThreadInfo* threadInfo, xmlrpc::message* msg) override;
	virtual xmlrpc::message* CreateMessage(const char* buffer, size_t msgSize) override;
private:
	bool HandleRpcCall(const std::string& function, xmlrpc::value& value);

private:
	//std::map<std::string, xmlrpc::methodPtr> m_rpcMethods;
	Daemon* m_daemon;

	xmlrpc::registry m_registry;
};