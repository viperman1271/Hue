#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

#include <string>
#include <iostream>

#include "RpcClient.h"

template<class T>
void print_size(const T&)
{
	std::cout << sizeof(T) << std::endl;
}
template<class T, class ... Args>
void print_size(const T &arg, Args... args)
{
	print_size(args...);
}

int main(int argc, char** argv)
{
	RpcClient client;
	client.Init();
	client.Receive();
	client.Close();

	print_size("J'aime mon prof", 3, 3.14159);
	print_size(3, "J'aime mon prof", 3.14159);

	return 0;
}