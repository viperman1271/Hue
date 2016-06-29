#include <string>
#include <iostream>

#include "RpcClient.h"

#include "methods/turn_on_lights.h"
#include "methods/turn_off_lights.h"

turn_on_lights turn_on_lights;
turn_off_lights turn_off_lights;

int main(int argc, char** argv)
{
	RpcClient client;
	client.Init();
	client.Receive();

	turn_on_lights.init(&client);
	turn_off_lights.init(&client);

	turn_off_lights.call();
	client.Close();

	return 0;
}