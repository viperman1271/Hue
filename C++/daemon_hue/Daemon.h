#pragma once

#ifdef LINUX
#include <pthread.h>
#endif // LINUX

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
#ifdef LINUX
		pthread_t thread;
#endif //LINUX
		Daemon* instance;
	};

private:
	HueBridge* m_bridge;
};