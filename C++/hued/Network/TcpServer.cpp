#include "Network/TcpServer.h"

#include <stdio.h>
#include <string.h>
#include <iostream>

#include "StatusMessage.h"

void TcpServer::Init()
{

}

bool TcpServer::HandleMessage(TcpServerThreadInfo* threadInfo, Message* msg)
{
	const StatusMessage closeMessage(StatusMessage::ID::CLOSE);
	if (msg == &closeMessage)
		return false;

	return true;
}

Message* TcpServer::CreateMessage(const char* buffer)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError err = doc.Parse(buffer);
	if (err != tinyxml2::XML_SUCCESS)
	{
		return nullptr;
	}

	if (tinyxml2::XMLElement* rootElem = doc.FirstChildElement("message"))
	{
		std::string type = rootElem->Attribute("type");
		return m_messages[type]();
	}

	return nullptr;
}
