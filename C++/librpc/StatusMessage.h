#pragma once

#include "Message.h"

class StatusMessage : public Message
{
public:
	enum class ID
	{
		UNKNOWN,
		WELCOME,
		CLOSE,
	};
	
	StatusMessage();
	StatusMessage(ID eMsgId);

	ID GetMessageID() const { return m_id; }

	bool operator==(const Message& rhs) const override;
	bool operator==(const Message* rhs) const override;

	const std::string& GetMsgStr() const { return s_msg; };
protected:
	void Handle(tinyxml2::XMLElement* in_pXmlElement) override;
	void Create(tinyxml2::XMLElement* in_pXmlElement) const override;
private:
	ID m_id;
	static std::string s_msg;
};