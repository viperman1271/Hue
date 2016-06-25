#include "StatusMessage.h"
#include <cassert>

std::string StatusMessage::s_msg = "status";

StatusMessage::StatusMessage()
	: m_id(ID::UNKNOWN)
{

}

StatusMessage::StatusMessage(ID eMsgId)
	: m_id(eMsgId)
{

}

bool StatusMessage::operator==(const Message* rhs) const
{
	return GetMsgStr() == rhs->GetMsgStr() && dynamic_cast<const StatusMessage*>(rhs)->m_id == m_id;
}

bool StatusMessage::operator==(const Message& rhs) const
{
	return this->operator==(&rhs);
}

void StatusMessage::Handle(tinyxml2::XMLElement* in_pXmlElement)
{
	tinyxml2::XMLElement* pFirstChildElement = in_pXmlElement->FirstChildElement();
	if (strcmp(pFirstChildElement->Name(), s_msg.c_str()) == 0)
	{
		const char* msgAttrVal = pFirstChildElement->Attribute("msg");
		if (strcmp(msgAttrVal, "welcome") == 0)
		{
			m_id = ID::WELCOME;
		}
	}
}

void StatusMessage::Create(tinyxml2::XMLElement* in_pXmlElement) const
{
	tinyxml2::XMLElement* xmlElement = in_pXmlElement->GetDocument()->NewElement(s_msg.c_str());
	switch (m_id)
	{
	case ID::WELCOME:
		xmlElement->SetAttribute("msg", "welcome");
		break;

	case ID::CLOSE:
		xmlElement->SetAttribute("msg", "close");
		break;

	default:
		assert(false);
	}
	in_pXmlElement->InsertFirstChild(xmlElement);
}