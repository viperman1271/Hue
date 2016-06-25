#pragma once

#include "Network/RpcMethod.h"

class TurnOnLightsRpcMethod : RpcMethod
{
	using super = RpcMethod;
public:
	TurnOnLightsRpcMethod();
	void Execute(RpcParamList const& paramList, RpcValue& returnVal) override;
};