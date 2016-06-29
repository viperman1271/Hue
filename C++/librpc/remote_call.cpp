#include <rpc-messages/remote_call.h>

std::string remote_call::s_msg = "rpc_call";

remote_call::remote_call(const std::string& remoteFunction)
	: m_function(remoteFunction)
{

}

remote_call::remote_call()
{

}

void remote_call::Handle(tinyxml2::XMLElement* in_pXmlElement)
{
	tinyxml2::XMLElement* pFirstChildElement = in_pXmlElement->FirstChildElement();
	if (strcmp(pFirstChildElement->Name(), s_msg.c_str()) == 0)
	{
		m_function = pFirstChildElement->Attribute("name");
	}
}

void remote_call::Create(tinyxml2::XMLElement* in_pXmlElement) const
{
	tinyxml2::XMLElement* xmlElement = in_pXmlElement->GetDocument()->NewElement(s_msg.c_str());
	
	xmlElement->SetAttribute("name", m_function.c_str());

	in_pXmlElement->InsertFirstChild(xmlElement);
}

