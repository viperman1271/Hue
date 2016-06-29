#pragma once

#include <xmlrpc/method.h>

class turn_on_lights : public xmlrpc::method
{
	using super = xmlrpc::method;
public:
	turn_on_lights();
	void execute(xmlrpc::param_list const& paramList, xmlrpc::value& returnVal) override;
};