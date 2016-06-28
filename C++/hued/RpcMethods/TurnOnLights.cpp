#include "TurnOnLights.h"
#include "Daemon.h"
#include "Network/RpcServer.h"

#include <HueBridge.h>

TurnOnLightsRpcMethod::TurnOnLightsRpcMethod()
	: super("", "Bridge.TurnOn")
{

}

void TurnOnLightsRpcMethod::execute(xmlrpc::param_list const& paramList, xmlrpc::value& returnVal)
{
	RpcServer* rpcServer;
	if(paramList[0]->get_value(rpcServer))
	{
		Daemon* daemon = rpcServer->GetDaemon();
		if (daemon == nullptr)
			return;

		HueBridge* bridge = daemon->GetBridge();
		if (bridge == nullptr)
			return;

		bridge->TurnOnLights();
	}
}

