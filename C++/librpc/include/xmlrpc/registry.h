#pragma once

#include <map>
#include <functional>

#include <xmlrpc/method.h>
#include <xmlrpc/registry.h>

namespace xmlrpc
{
class message;

class registry
{
public:
	void addMethod(const std::string& methodName, xmlrpc::methodPtr methodPtr);

	template<class... T>
	void callMethod(const std::string& methodName, T... args);
	void callMethod(const std::string& methodName, xmlrpc::param_list& paramList);

	void registerMessage(const std::string& messageName, std::function<xmlrpc::message*(void)>& function);
	message* createMessage(const std::string& data) const;
private:
	std::map<std::string, std::function<xmlrpc::message*(void)>> m_messages;
	std::map<std::string, xmlrpc::methodPtr> m_methods;

	std::vector<std::string>* m_serializer;
};
}

#include <xmlrpc/registry.hpp>