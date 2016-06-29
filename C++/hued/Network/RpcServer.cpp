#include "RpcServer.h"

#include <rpc-messages/remote_call.h>
#include <rpc-messages/return_value.h>
#include <xmlrpc/registry.h>

#include "methods/turn_on_lights.h"
#include "methods/turn_off_lights.h"

#include <iostream>

RpcServer::RpcServer(Daemon* daemon)
	: m_daemon(daemon)
{
	m_registry.addMethod("Bridge.TurnOn", xmlrpc::methodPtr(new turn_on_lights()));
	m_registry.addMethod("Bridge.TurnOff", xmlrpc::methodPtr(new turn_off_lights()));

	std::string msgName{ "rpc_call" };
	std::function<xmlrpc::message*(void)> msg = []() { return new remote_call(); };
	m_registry.registerMessage(msgName, msg);
}

void RpcServer::Run()
{
	Init();
	super::Run();
}

bool RpcServer::HandleMessage(TcpServerThreadInfo* threadInfo, xmlrpc::message* msg)
{
	if (msg->GetMsgStr() == "rpc_call")
	{
		remote_call* rpcMsg = dynamic_cast<remote_call*>(msg);
		xmlrpc::value value;
		bool returnVal = HandleRpcCall(rpcMsg->GetFunc(), value);

		return_value* sendMessage = new return_value(value);
		TransmitMessage(threadInfo, sendMessage);
		delete sendMessage;

		return returnVal;
	}
	else
	{
		return super::HandleMessage(threadInfo, msg);
	}
}

xmlrpc::message* RpcServer::CreateMessage(const char* buffer, size_t msgSize)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError err = doc.Parse(buffer, msgSize);
	if (err != tinyxml2::XML_SUCCESS)
	{
		return nullptr;
	}

	if (tinyxml2::XMLElement* rootElem = doc.FirstChildElement("message"))
	{
		std::string type = rootElem->Attribute("type");
		return m_registry.createMessage(type);
	}

	return nullptr;
}

bool RpcServer::HandleRpcCall(const std::string& function, xmlrpc::value& value)
{
	xmlrpc::param_list paramList;
	paramList.push_back(xmlrpc::value::create(this));

	m_registry.callMethod(function, paramList);

	for (xmlrpc::value* val : paramList)
	{
		delete val;
	}

	return true;
}
