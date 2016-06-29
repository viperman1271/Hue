#pragma once

#include <string>
#include <tinyxml2.h>

namespace xmlrpc
{
class message
{
public:
	message();
	virtual ~message();

	void serialize();
	void deserialize(const char* in_pszMessage, size_t in_uBytes);

	const std::string& GetRawMsg() const { return m_message; }

	virtual bool operator==(const message& rhs) const;
	virtual bool operator==(const message* rhs) const;

	virtual const std::string& GetMsgStr() const { return ms_blankMessage; }
protected:
	virtual void Handle(tinyxml2::XMLElement* in_pXmlElement) { }
	virtual void Create(tinyxml2::XMLElement* in_pXmlElement) const { }

private:
	tinyxml2::XMLDocument m_doc;
	std::string m_message;
	static const std::string ms_blankMessage;
};
}
