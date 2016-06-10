#include "Daemon.h"
#include <libhue/Platform.h>
#include <iostream>
#include "HueBridge.h"
#include "HueBridgeLocator.h"

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
	ThreadInfo tcpClientListener;

	auto pThreadReturn = pthread_create(&tcpClientListener.thread, nullptr, &TcpClientListenerThread, reinterpret_cast<void*>(&tcpClientListener));
	if (pThreadReturn != 0)
	{
		return -1;
	}

	ThreadInfo httpClientListener;

	pThreadReturn = pthread_create(&httpClientListener.thread, nullptr, &HttpFileGeneratorThread, reinterpret_cast<void*>(&httpClientListener));
	if (pThreadReturn != 0)
	{
		return -2;
	}

	pthread_join(tcpClientListener.thread, nullptr);
	pthread_join(httpClientListener.thread, nullptr);

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
		HUEPLATFORM::SLEEP(secDuration);
	}
	return nullptr;
}

void* Daemon::TcpClientListenerThread(void* ptr)
{
	ThreadInfo* threadInfo = reinterpret_cast<ThreadInfo*>(ptr);

	const std::chrono::seconds secDuration = std::chrono::seconds(1);

	while (true)
	{
		//HUEPLATFORM::SLEEP(secDuration);
	}
	return nullptr;
}
