#include <xmlrpc/registry.h>
#include <iostream>

namespace xmlrpc
{
void registry::addMethod(const std::string& methodName, xmlrpc::methodPtr methodPtr)
{
	if (m_methods.find(methodName) == m_methods.end())
	{
		m_methods[methodName] = methodPtr;
	}
}

void registry::registerMessage(const std::string& messageName, std::function<message*(void)>& function)
{
}

message* registry::createMessage(const std::string& data) const
{
	return nullptr;
}
}
