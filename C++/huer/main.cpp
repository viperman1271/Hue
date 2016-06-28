#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

#include <string>
#include <iostream>

#include "RpcClient.h"

int main(int argc, char** argv)
{
	/*std::string const serverUrl("http://raspbian-download:8888/RPC2");
	std::string const methodName("sample.add");

	xmlrpc_c::clientSimple myClient;
	xmlrpc_c::value result;

	myClient.call(serverUrl, methodName, "ii", &result, 5, 7);

	int const sum = xmlrpc_c::value_int(result);
	// Assume the method returned an integer; throws error if not

	std::cout << "Result of RPC (sum of 5 and 7): " << sum << std::endl;*/

	RpcClient client;
	client.Run();

	return 0;
}