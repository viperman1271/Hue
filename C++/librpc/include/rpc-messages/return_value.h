#pragma once

#include <xmlrpc/message.h>
#include <xmlrpc/value.h>

class return_value : public xmlrpc::message
{
public:
	return_value(xmlrpc::value& value);

	const std::string& GetMsgStr() const { return s_msg; };
	const std::string& GetType() const { return m_type; }
	const std::string& GetValue() const { return m_value; }
protected:
	void Handle(tinyxml2::XMLElement* in_pXmlElement) override;
	void Create(tinyxml2::XMLElement* in_pXmlElement) const override;
private:
	static std::string s_msg;
	std::string m_type;
	std::string m_value;
};