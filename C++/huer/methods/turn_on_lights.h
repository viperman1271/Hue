#pragma once

#include <xmlrpc/method.h>

#include "RpcClient.h"

class turn_on_lights : public xmlrpc::remote_method<void>
{
public:
	void init(RpcClient* client);
	void call() override;
private:
	RpcClient* m_client;
};
