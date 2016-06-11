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
		std::thread thread;
		Daemon* instance;
	};

private:
	HueBridge* m_bridge;
};