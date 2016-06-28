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

	template<class... T>
	void callMethod(const std::string& methodName, T... args);

	void registerMessage(const std::string& messageName, std::function<message*(void)>& function);
	message* createMessage(const std::string& data) const;
private:
	class serializer
	{
	public:
		template<class T>
		void serialize(const T& value);

		template<class T, class... Args>
		void serialize(const T& value, Args... args);

		const std::vector<std::string>& get_serialized() const { return serialized; }

	private:
		std::vector<std::string> serialized;
	};
private:
	std::map<std::string, std::function<message*(void)>> m_messages;
	std::map<std::string, xmlrpc::methodPtr> m_methods;

	std::vector<std::string>* m_serializer;
};
}

#include <xmlrpc/registry.hpp>
