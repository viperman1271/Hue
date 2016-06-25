#pragma once

#ifdef LINUX
#include <pthread.h>
#endif // LINUX
#include <thread>
#include <chrono>
#include <vector>

#include "ObjectModel/HueLightInformation.h"
#include "PresenceFile.h"

class HueBridge;

class Daemon
{
public:
	Daemon(const Daemon& rhs) = delete;
	Daemon& operator==(const Daemon& rhs) = delete;

	static int Run();

	static void* GenericUpdateThread(void* ptr);
	static void* TcpClientListenerThread(void* ptr);

	HueBridge* GetBridge() const { return m_bridge; }
private:
	Daemon();
	int RunImpl();
	void UpdateBridgeInfo();
	void GenerateHtmlFile();
	bool DetectPresenceWithDevices();
	void ProcessEnergySaving(bool presentDevice);

private:
	struct ThreadInfo
	{
        ThreadInfo(Daemon* in_pInstance) : instance{ in_pInstance } { }
        
        ThreadInfo() = delete;
        ThreadInfo(const ThreadInfo& rhs) = delete;
        ThreadInfo& operator==(const ThreadInfo& rhs) = delete;

		std::thread thread;
		Daemon* instance;
	};

private:
	HueBridge* m_bridge;
	PresenceFile m_presentFile;

	std::vector<HueLightInformation> m_activeLights;
};