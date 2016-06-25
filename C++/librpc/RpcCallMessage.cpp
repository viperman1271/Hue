#include "RpcCallMessage.h"

std::string RpcCallMessage::s_msg = "rpc_call";

void RpcCallMessage::Handle(tinyxml2::XMLElement* in_pXmlElement)
{
	tinyxml2::XMLElement* pFirstChildElement = in_pXmlElement->FirstChildElement();
	if (strcmp(pFirstChildElement->Name(), s_msg.c_str()) == 0)
	{
		m_function = pFirstChildElement->Attribute("name");
	}
}

void RpcCallMessage::Create(tinyxml2::XMLElement* in_pXmlElement) const
{
	tinyxml2::XMLElement* xmlElement = in_pXmlElement->GetDocument()->NewElement(s_msg.c_str());
	
	xmlElement->SetAttribute("name", m_function.c_str());

	in_pXmlElement->InsertFirstChild(xmlElement);
}

