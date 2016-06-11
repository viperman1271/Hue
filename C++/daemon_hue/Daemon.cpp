#include "Daemon.h"
#include <libhue/Platform.h>
#include <iostream>
#include <thread>
#include "HueBridge.h"
#include "HueBridgeLocator.h"
#include <thread>

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
	ThreadInfo tcpServerThread;
	tcpServerThread.thread = std::thread{ TcpClientListenerThread, reinterpret_cast<void*>(&tcpServerThread) };

	ThreadInfo httpGenThread;
	httpGenThread.thread = std::thread{ HttpFileGeneratorThread, reinterpret_cast<void*>(&httpGenThread) };

	tcpServerThread.thread.join();
	httpGenThread.thread.join();

	return 0;
}

void Daemon::GenerateHtmlFile()
{

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

	m_bridge->TryUpdateAllData();
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
