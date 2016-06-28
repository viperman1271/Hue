#pragma once

#include <map>
#include <functional>

#include <xmlrpc/method.h>

namespace xmlrpc
{
class message;

class registry
{
public:
	void addMethod(const std::string& methodName, xmlrpc::methodPtr methodPtr);
	void callMethod(const std::string& methodName);

	void registerMessage(const std::string& messageName, std::function<message*(void)>& function);
	message* createMessage(const std::string& data) const;
private:
	std::map<std::string, std::function<message*(void)>> m_messages;
	std::map<std::string, xmlrpc::methodPtr> m_methods;
};
}