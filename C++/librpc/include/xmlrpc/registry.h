#pragma once

#include <map>

namespace xmlrpc
{
class registry
{
public:
	void addMethod(const std::string& methodName, xmlrpc::methodPtr);

private:
	std::map<std::string, std::function<Message*(void)>> m_messages;
};
}