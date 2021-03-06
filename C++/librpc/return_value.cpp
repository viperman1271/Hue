#include <rpc-messages/return_value.h>

std::string return_value::s_msg = "rpc_return_val";

return_value::return_value(xmlrpc::value& value)
	: m_type(value.get_type())
	, m_value(value.get_value())
{

}

void return_value::Handle(tinyxml2::XMLElement* in_pXmlElement)
{
	tinyxml2::XMLElement* pFirstChildElement = in_pXmlElement->FirstChildElement();
	if (strcmp(pFirstChildElement->Name(), s_msg.c_str()) == 0)
	{
		m_type = pFirstChildElement->Attribute("type");
		m_value = pFirstChildElement->Attribute("value");
	}
}

void return_value::Create(tinyxml2::XMLElement* in_pXmlElement) const
{
	tinyxml2::XMLElement* xmlElement = in_pXmlElement->GetDocument()->NewElement(s_msg.c_str());

	xmlElement->SetAttribute("type", m_type.c_str());
	xmlElement->SetAttribute("value", m_value.c_str());

	in_pXmlElement->InsertFirstChild(xmlElement);
}
