#pragma once

#include <xmlrpc/message.h>

class status : public xmlrpc::message
{
public:
	enum class ID
	{
		UNKNOWN,
		WELCOME,
		CLOSE,
	};
	
	status();
	status(ID eMsgId);

	ID GetMessageID() const { return m_id; }

	bool operator==(const xmlrpc::message& rhs) const override;
	bool operator==(const xmlrpc::message* rhs) const override;

	const std::string& GetMsgStr() const { return s_msg; };
protected:
	void Handle(tinyxml2::XMLElement* in_pXmlElement) override;
	void Create(tinyxml2::XMLElement* in_pXmlElement) const override;
private:
	ID m_id;
	static std::string s_msg;
};