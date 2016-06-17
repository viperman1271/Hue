#include "Daemon.h"
#include <libhue/Platform.h>
#include "HueBridge.h"
#include "HueBridgeLocator.h"
#include "IniFile.h"
#include "LibHue.h"

#include <tinyxml2.h>

#include <fstream>
#include <iostream>
#include <regex>
#include <thread>
#include <iomanip>
#include <sstream>
#include <cassert>

#ifdef LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pwd.h>
#endif //LINUX

int Daemon::Run()
{
	Daemon d;
	return d.RunImpl();
}

Daemon::Daemon()
	: m_bridge(nullptr)
	, m_presentDevices(true)
{

}

int Daemon::RunImpl()
{
    ThreadInfo tcpServerThread{ this };
	tcpServerThread.thread = std::thread{ TcpClientListenerThread, reinterpret_cast<void*>(&tcpServerThread) };

    ThreadInfo updateThread{ this };
	updateThread.thread = std::thread{ GenericUpdateThread, reinterpret_cast<void*>(&updateThread) };

	tcpServerThread.thread.join();
	updateThread.thread.join();

	return 0;
}

void Daemon::UpdateBridgeInfo()
{
	if (m_bridge == nullptr)
	{
		m_bridge = HueBridgeLocator::Locate();
		if (m_bridge == nullptr)
		{
			std::cerr << "Cannot locate bridge" << std::endl;
		}
	}

	if (m_bridge)
	{
		m_bridge->TryUpdateAllData();
	}
}

void Daemon::GenerateHtmlFile()
{
    std::ofstream file;
    file.open(IniFile::GetInstance()->GetHttpFilePath());
    if (!file.is_open())
    {
        return;
    }

    file << R"(<html>
    <title>Philips Hue Dashboard</title>
    <head><link rel="icon" href="http://mikefilion.com/images/favicon.png"></head>
    <body>)" << std::endl;
    file << "        After sunset: " << (m_bridge->IsAfterSunset() ? "Yes" : "No") << std::endl;
    file << R"(        <table border="1" style="width:100%">)" << std::endl;
    file << "            <tr>" << std::endl;
    file << "                <th></th>" << std::endl;
    for (const auto& light : m_bridge->info.lights)
    {
        file << "                <th>" << light.name << "</th>" << std::endl;
    }
    file << "            </tr>" << std::endl;
    file << "            <tr>" << std::endl;
    file << "                <td>On</td>" << std::endl;
    for (const auto& light : m_bridge->info.lights)
    {
		if (light.state.on)
		{
			file << R"(                <td bgcolor="#8CFFA1">)" << (light.state.on ? "Yes" : "No") << "</td>" << std::endl;
		}
		else
		{
			file << R"(                <td bgcolor="#FFBCDC">)" << (light.state.on ? "Yes" : "No") << "</td>" << std::endl;
		}
    }
    file << "            </tr>" << std::endl;
    file << "            <tr>" << std::endl;
    file << "                <td>Reachable</td>" << std::endl;
    for (const auto& light : m_bridge->info.lights)
    {
		if (light.state.reachable)
		{
			file << R"(                <td bgcolor="#8CFFA1">)" << (light.state.reachable ? "Yes" : "No") << "</td>" << std::endl;
		}
		else
		{
			file << R"(                <td bgcolor="#FFBCDC">)" << (light.state.reachable ? "Yes" : "No") << "</td>" << std::endl;
		}
    }
    file << "            </tr>" << std::endl;
    file << "        </table>" << std::endl;
    file << "    </body>" << std::endl;
    file << "</html>";

    file.close();
}

void Daemon::DetectPresenceWithDevices()
{
	std::ifstream iniFile;
#ifdef LINUX
	struct passwd* pw = getpwuid(getuid());
	const char* homedir = pw->pw_dir;

	std::stringstream ss;
	ss << homedir << "/huedpd.xml";

	struct stat buffer;
	if (stat(ss.str().c_str(), &buffer) == 0)
	{
		remove(ss.str().c_str());
	}
	system("nmap -sP 10.0.0.1-255 -oX ~/huedpd.xml");
#endif // LINUX
#ifdef LINUX
	iniFile.open(ss.str().c_str());
#else
	iniFile.open(R"(D:\huedpd.xml)");
#endif // LINUX
	
	if (!iniFile.is_open())
	{
		return;
	}

	m_presentDevices = false;

	iniFile.seekg(0, std::ios::end);
	int fileSize = static_cast<int>(iniFile.tellg());
	iniFile.seekg(0, std::ios::beg);

	char* pszFileContents = new char[fileSize + 1];
	memset(pszFileContents, 0, fileSize + 1);
	iniFile.read(pszFileContents, fileSize);

	std::string fileContents{ pszFileContents };
	delete [] pszFileContents;
	pszFileContents = nullptr;

	auto index = fileContents.find("<nmaprun");
	fileContents = fileContents.substr(index);

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError err = doc.Parse(fileContents.c_str());
	if(err != tinyxml2::XML_SUCCESS)
	{ 
		return;
	}

	if (tinyxml2::XMLElement* rootElem = doc.FirstChildElement("nmaprun"))
	{
		for (tinyxml2::XMLElement* childElem = rootElem->FirstChildElement(); childElem != nullptr; childElem = childElem->NextSiblingElement())
		{
			if (childElem == nullptr)
				continue;

			if (strcmp(childElem->Name(), "host") != 0)
				continue;

			bool isStateUp = false;
			if(tinyxml2::XMLElement* statusElem = childElem->FirstChildElement("status"))
			{ 
				isStateUp = strcmp(statusElem->Attribute("state"), "up") == 0;
			}

			std::vector<std::string> hostnames;
			if (tinyxml2::XMLElement* hostnamesElem = childElem->FirstChildElement("hostnames"))
			{
				for (tinyxml2::XMLElement* hostnameElem = hostnamesElem->FirstChildElement(); hostnameElem != nullptr; hostnameElem = hostnameElem->NextSiblingElement())
				{
					if (hostnameElem == nullptr || strcmp(hostnameElem->Name(), "hostname") != 0)
						continue;

					hostnames.emplace_back(hostnameElem->Attribute("name"));
				}

				for (std::string& name : hostnames)
				{
					if (name.find("android-") != std::string::npos && isStateUp)
					{
						m_presentDevices = true;
						m_lastPresentDeviceTime = std::chrono::system_clock::now();
						break;
					}
				}
			}
		}
	}
}

void Daemon::ProcessEnergySaving()
{
	if (m_bridge == nullptr)
		return;

	if (!m_presentDevices)
	{
		for (const auto& light : m_bridge->info.lights)
		{
			m_bridge->TurnOffLight(light);
		}
	}
	
	m_activeLights.clear();

	if(!m_presentDevices)
	{
		for (const auto& light : m_bridge->info.lights)
		{
			if (light.state.on)
			{
				m_activeLights.push_back(light);
			}
		}
	}
}

void* Daemon::GenericUpdateThread(void* ptr)
{
	ThreadInfo* threadInfo = reinterpret_cast<ThreadInfo*>(ptr);
	Daemon* daemon = threadInfo->instance;

	const std::chrono::seconds secDuration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::minutes(5));

	while (true)
	{
		daemon->UpdateBridgeInfo();
		daemon->GenerateHtmlFile();
		daemon->DetectPresenceWithDevices();
		daemon->ProcessEnergySaving();

		std::this_thread::sleep_for(secDuration);
	}
	return nullptr;
}

void* Daemon::TcpClientListenerThread(void* ptr)
{
	ThreadInfo* threadInfo = reinterpret_cast<ThreadInfo*>(ptr);
	assert(threadInfo != nullptr);

	const std::chrono::seconds secDuration = std::chrono::seconds(1);

	while (true)
	{
		std::this_thread::sleep_for(secDuration);
	}
	return nullptr;
}
