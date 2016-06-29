#include <xmlrpc/message.h>

namespace xmlrpc
{
const std::string message::ms_blankMessage = "";

message::message()
{

}

message::~message()
{

}

void message::serialize()
{
	tinyxml2::XMLElement* rootElem = m_doc.NewElement("message");
	rootElem->SetAttribute("type", GetMsgStr().c_str());
	Create(rootElem);
	m_doc.InsertFirstChild(rootElem);

	tinyxml2::XMLPrinter printer;
	m_doc.Print(&printer);
	m_message = printer.CStr();
	m_message += "\0";
}

void message::deserialize(const char* in_pszMessage, size_t in_uBytes)
{
	m_message = in_pszMessage;

	tinyxml2::XMLError err = m_doc.Parse(in_pszMessage, in_uBytes);
	if (err != tinyxml2::XML_SUCCESS)
	{
		return;
	}

	if (tinyxml2::XMLElement* rootElem = m_doc.FirstChildElement("message"))
	{
		Handle(rootElem);
	}
}

bool message::operator==(const message* rhs) const
{
	return GetMsgStr() == rhs->GetMsgStr();
}

bool message::operator==(const message& rhs) const
{
	return this->operator==(&rhs);
}
}
