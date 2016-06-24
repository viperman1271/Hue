#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <mutex>

#include <tinyxml2.h>

class PresenceFile
{
	struct DetectedPresenceDevice
	{
		DetectedPresenceDevice() { }
		DetectedPresenceDevice(const char* in_pszIpAddress) : ipAdress(in_pszIpAddress) { }

		std::string ipAdress;
		unsigned int totalCount = 0;
	};
public:
	bool DetectPresenceWithDevices();
	bool DetectSpecificPresencesWithDevices();
private:
	bool		ProcessPresenceFile();
	bool		DetectPresenceWithDeviceList(std::vector<DetectedPresenceDevice>& deviceIpAddresses);
	static int  ReadFileSize(std::ifstream& file);
	static void ReadFileContents(std::ifstream& file, std::string& fileContents, int fileSize);
	static bool IsPresenceDevice(tinyxml2::XMLElement* childElem, bool isStateUp);
private:
	bool m_presentDevices;
	std::mutex m_mutex;

	std::vector<DetectedPresenceDevice> m_deviceIpAddresses;
	std::chrono::system_clock::time_point m_lastPresentDeviceTime;
};