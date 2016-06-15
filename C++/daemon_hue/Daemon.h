#pragma once

#ifdef LINUX
#include <pthread.h>
#endif // LINUX
#include <thread>

class HueBridge;

class Daemon
{
public:
	Daemon(const Daemon& rhs) = delete;
	Daemon& operator==(const Daemon& rhs) = delete;

	static int Run();

	static void* HttpFileGeneratorThread(void* ptr);
	static void* TcpClientListenerThread(void* ptr);

private:
	Daemon();
	int RunImpl();
	void GenerateHtmlFile();
	void UpdateBridgeInfo();

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
};