#pragma once

#include <xmlrpc/method.h>

class turn_off_lights : public xmlrpc::method
{
	using super = xmlrpc::method;
public:
	turn_off_lights();
	void execute(xmlrpc::param_list const& paramList, xmlrpc::value& returnVal) override;
};