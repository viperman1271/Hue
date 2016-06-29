#include "turn_off_lights.h"
#include <rpc-messages/remote_call.h>

void turn_off_lights::init(RpcClient* client)
{
	m_client = client;
}

void turn_off_lights::call()
{
	remote_call callMessage("Bridge.TurnOff");
	m_client->Send(&callMessage);
}
