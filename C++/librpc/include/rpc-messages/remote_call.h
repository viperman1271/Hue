#pragma once

#include <xmlrpc/message.h>

class remote_call : public xmlrpc::message
{
public:
	remote_call(const std::string& remoteFunction);
	remote_call();

	const std::string& GetMsgStr() const { return s_msg; };
	const std::string& GetFunc() const { return m_function; }

	void set_function(const std::string& function) { m_function = function; }
protected:
	void Handle(tinyxml2::XMLElement* in_pXmlElement) override;
	void Create(tinyxml2::XMLElement* in_pXmlElement) const override;
private:
	static std::string s_msg;
	std::string m_function;
};