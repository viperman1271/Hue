#include "RpcServer.h"
#include "RpcCallMessage.h"
#include "RpcReturnMessage.h"

#include "Network/RpcMethod.h"

#include <iostream>

RpcServer::RpcServer(Daemon* daemon)
	: m_daemon(daemon)
{

}

void RpcServer::Run()
{
	Init();
	super::Run();
}

void RpcServer::RegisterFunction(RpcMethod* method)
{
	m_rpcMethods[method->GetName()] = method;
}

bool RpcServer::HandleMessage(TcpServerThreadInfo* threadInfo, Message* msg)
{
	if (msg->GetMsgStr() == "rpc_call")
	{
		RpcCallMessage* rpcMsg = dynamic_cast<RpcCallMessage*>(msg);
		RpcValue value;
		bool returnVal = HandleRpcCall(rpcMsg->GetFunc(), value);

		Message* sendMessage = new RpcReturnMessage(value);
		TransmitMessage(threadInfo, sendMessage);
		delete sendMessage;

		return returnVal;
	}
	else
	{
		return super::HandleMessage(threadInfo, msg);
	}
}

bool RpcServer::HandleRpcCall(const std::string& function, RpcValue& value)
{
	RpcParamList paramList;
	paramList.push_back(RpcValue::Create(this));

	m_rpcMethods[function]->Execute(paramList, value);

	for (RpcValue* val : paramList)
	{
		delete val;
	}

	return true;
}
