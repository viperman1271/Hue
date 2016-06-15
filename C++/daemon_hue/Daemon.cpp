#include "Daemon.h"
#include <libhue/Platform.h>
#include "HueBridge.h"
#include "HueBridgeLocator.h"
#include "IniFile.h"
#include "LibHue.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <thread>
#include <iomanip>
#include <sstream>

#ifdef LINUX
#include <sys/types.h>
#include <sys/socket.h>
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

    ThreadInfo httpGenThread{ this };
	httpGenThread.thread = std::thread{ HttpFileGeneratorThread, reinterpret_cast<void*>(&httpGenThread) };

	tcpServerThread.thread.join();
	httpGenThread.thread.join();

	return 0;
}

//#include <string>

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
        file << "                <td>" << (light.state.on ? "Yes" : "No") << "</td>" << std::endl;
    }
    file << "            </tr>" << std::endl;
    file << "            <tr>" << std::endl;
    file << "                <td>Reachable</td>" << std::endl;
    for (const auto& light : m_bridge->info.lights)
    {
        file << "                <td>" << (light.state.reachable ? "Yes" : "No") << "</td>" << std::endl;
    }
    file << "            </tr>" << std::endl;
    file << "        </table>" << std::endl;
    file << "    </body>" << std::endl;
    file << "</html>";

    file.close();
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

void* Daemon::HttpFileGeneratorThread(void* ptr)
{
	ThreadInfo* threadInfo = reinterpret_cast<ThreadInfo*>(ptr);
	Daemon* daemon = threadInfo->instance;

	const std::chrono::seconds secDuration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::minutes(5));

	while (true)
	{
		daemon->UpdateBridgeInfo();
		daemon->GenerateHtmlFile();

		std::this_thread::sleep_for(secDuration);
	}
	return nullptr;
}

void* Daemon::TcpClientListenerThread(void* ptr)
{
	ThreadInfo* threadInfo = reinterpret_cast<ThreadInfo*>(ptr);

	const std::chrono::seconds secDuration = std::chrono::seconds(1);

	while (true)
	{
		std::this_thread::sleep_for(secDuration);
	}
	return nullptr;
}
