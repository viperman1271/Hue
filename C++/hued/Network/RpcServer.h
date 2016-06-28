#pragma once

#include "Network/TcpServer.h"

#include <xmlrpc/message.h>

class RpcMethod;
class RpcValue;
class Daemon;

class RpcServer : public TcpServer
{
	using super = TcpServer;
public:
	RpcServer(Daemon* daemon);

	void Run() override;
	void RegisterFunction(RpcMethod* method);
	Daemon* GetDaemon() const { return m_daemon; }

protected:
	bool HandleMessage(TcpServerThreadInfo* threadInfo, xmlrpc::message* msg) override;

private:
	bool HandleRpcCall(const std::string& function, RpcValue& value);

private:
	std::map<std::string, RpcMethod*> m_rpcMethods;
	Daemon* m_daemon;
};