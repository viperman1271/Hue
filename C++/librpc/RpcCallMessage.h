#pragma once

#include <xmlrpc/message.h>

class RpcCallMessage : public xmlrpc::message
{
public:
	const std::string& GetMsgStr() const { return s_msg; };
	const std::string& GetFunc() const { return m_function; }
protected:
	void Handle(tinyxml2::XMLElement* in_pXmlElement) override;
	void Create(tinyxml2::XMLElement* in_pXmlElement) const override;
private:
	static std::string s_msg;
	std::string m_function;
};