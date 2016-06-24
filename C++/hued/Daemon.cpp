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
#include <mutex>

#ifdef LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#endif //LINUX

int Daemon::Run()
{
	Daemon d;
	return d.RunImpl();
}

Daemon::Daemon()
	: m_bridge(nullptr)
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

bool Daemon::DetectPresenceWithDevices()
{
	return m_presentFile.DetectPresenceWithDevices();
}

void Daemon::ProcessEnergySaving(bool presentDevice)
{
	if (m_bridge == nullptr)
		return;

	if (!presentDevice)
	{
		for (const auto& light : m_bridge->info.lights)
		{
			m_bridge->TurnOffLight(light);
		}
	}
	
	m_activeLights.clear();

	if(!presentDevice)
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
		if(IniFile::GetInstance()->GetEnergySaving())
		{
			bool present = daemon->DetectPresenceWithDevices();
			daemon->ProcessEnergySaving(present);
		}
		daemon->GenerateHtmlFile();

		std::this_thread::sleep_for(secDuration);
	}
	return nullptr;
}

/*void* Daemon::SpecificPresenceDetector()
{
	ThreadInfo* threadInfo = reinterpret_cast<ThreadInfo*>(ptr);
	Daemon* daemon = threadInfo->instance;

	const std::chrono::seconds secDuration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::minutes(1));

	while (true)
	{

	}
}*/

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
