#include "DumpJson.h"
#include "HueBridge.h"
#include "HttpClient.h"

#include <fstream>

DumpJsonCommand::DumpJsonCommand() 
	: super("dump")
{

}

void DumpJsonCommand::Execute()
{
	std::string url = m_bridge->Urls.GetStatusUrl();
	std::string responseFromServer = HttpClient::GetInstance()->Get(url);
	
	Json::Value root;
	Json::Reader reader;
	reader.parse(responseFromServer, root);

	std::ofstream file;
	file.open("hue_data.json");

	if (!file.is_open())
		return;

	file << root;

	file.close();
}
