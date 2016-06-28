#pragma once

#include <xmlrpc/method.h>

class TurnOnLightsRpcMethod : xmlrpc::method
{
	using super = xmlrpc::method;
public:
	TurnOnLightsRpcMethod();
	void execute(xmlrpc::param_list const& paramList, xmlrpc::value& returnVal) override;
};