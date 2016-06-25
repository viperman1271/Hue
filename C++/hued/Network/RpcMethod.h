#pragma once

#include "Network/RpcParamList.h"
#include "RpcValue.h"

#include <string>

class RpcMethod
{
public:
	virtual void Execute(RpcParamList const& paramList, RpcValue& returnVal) = 0;
	const std::string& GetName() const { return m_name; }

protected:
	RpcMethod(const std::string& help, const std::string& name)
		: m_help(help)
		, m_name(name)
	{

	}

private:
	const std::string m_help;
	const std::string m_name;
};