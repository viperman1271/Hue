#include "Message.h"

Message::~Message()
{

}

void Message::Serialize()
{
	tinyxml2::XMLElement* rootElem = m_doc.NewElement("message");
	rootElem->SetAttribute("type", GetMsgStr().c_str());
	Create(rootElem);
	m_doc.InsertFirstChild(rootElem);

	tinyxml2::XMLPrinter printer;
	m_doc.Print(&printer);
	m_message = printer.CStr();
}

void Message::Deserialize(const std::string& in_pszMessage)
{
	m_message = in_pszMessage;

	tinyxml2::XMLError err = m_doc.Parse(in_pszMessage.c_str());
	if (err != tinyxml2::XML_SUCCESS)
	{
		return;
	}

	if (tinyxml2::XMLElement* rootElem = m_doc.FirstChildElement("message"))
	{
		Handle(rootElem);
	}
}

bool Message::operator==(const Message* rhs) const
{
	return GetMsgStr() == rhs->GetMsgStr();
}

bool Message::operator==(const Message& rhs) const
{
	return this->operator==(&rhs);
}

