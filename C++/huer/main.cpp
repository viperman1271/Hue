#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

#include <string>
#include <iostream>

#include "RpcClient.h"

int main(int argc, char** argv)
{
	RpcClient client;
	client.Init();
	client.Receive();
	client.Close();

	return 0;
}