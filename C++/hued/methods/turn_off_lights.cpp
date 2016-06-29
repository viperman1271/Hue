#include "turn_off_lights.h"
#include "Daemon.h"
#include "Network/RpcServer.h"

#include <HueBridge.h>

turn_off_lights::turn_off_lights()
	: super("", "Bridge.TurnOff")
{

}

void turn_off_lights::execute(xmlrpc::param_list const& paramList, xmlrpc::value& returnVal)
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

		bridge->TurnOffLights();
	}
}

