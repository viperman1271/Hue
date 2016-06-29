#include <rpc-messages/status.h>
#include <cassert>

std::string status::s_msg = "status";

status::status()
	: m_id(ID::UNKNOWN)
{

}

status::status(ID eMsgId)
	: m_id(eMsgId)
{

}

bool status::operator==(const xmlrpc::message* rhs) const
{
	return GetMsgStr() == rhs->GetMsgStr() && dynamic_cast<const status*>(rhs)->m_id == m_id;
}

bool status::operator==(const xmlrpc::message& rhs) const
{
	return this->operator==(&rhs);
}

void status::Handle(tinyxml2::XMLElement* in_pXmlElement)
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

void status::Create(tinyxml2::XMLElement* in_pXmlElement) const
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