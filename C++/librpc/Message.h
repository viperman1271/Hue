#pragma once

#include <string>
#include <tinyxml2.h>

class Message
{
public:
	virtual ~Message();

	void Serialize();
	void Deserialize(const std::string& in_pszMessage);

	const std::string& GetRawMsg() const { return m_message; }

	virtual bool operator==(const Message& rhs) const;
	virtual bool operator==(const Message* rhs) const;

	virtual const std::string& GetMsgStr() const = 0;
protected:
	virtual void Handle(tinyxml2::XMLElement* in_pXmlElement) = 0;
	virtual void Create(tinyxml2::XMLElement* in_pXmlElement) const = 0;

private:
	tinyxml2::XMLDocument m_doc;
	std::string m_message;
};
