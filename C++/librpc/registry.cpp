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

void registry::callMethod(const std::string& methodName, xmlrpc::param_list& paramList)
{
	if (m_methods.find(methodName) == m_methods.end())
		return;

	xmlrpc::value returnValue;
	m_methods[methodName]->execute(paramList, returnValue);
}

void registry::registerMessage(const std::string& messageName, std::function<xmlrpc::message*(void)>& function)
{
	if (m_messages.find(messageName) == m_messages.end())
	{
		m_messages[messageName] = function;
	}
}

message* registry::createMessage(const std::string& data) const
{
	if (m_messages.find(data) == m_messages.end())
		return nullptr;

	//HACK
	return const_cast<registry*>(this)->m_messages[data]();
}
}
