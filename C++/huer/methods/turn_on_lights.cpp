#include "turn_on_lights.h"
#include <rpc-messages/remote_call.h>

void turn_on_lights::init(RpcClient* client)
{
	m_client = client;
}

void turn_on_lights::call()
{
	remote_call callMessage("Bridge.TurnOn");
	m_client->Send(&callMessage);
}
