#include "PresenceFile.h"
#include "IniFile.h"

#ifdef LINUX
#include <sys/stat.h>
#endif //LINUX

#include <sstream>
#include <fstream>

bool PresenceFile::DetectPresenceWithDevices()
{
	std::lock_guard<std::mutex> autoLock(m_mutex);
#ifdef LINUX
	struct stat buffer;
	if (stat(IniFile::GetInstance()->GetNmapFilePath().c_str(), &buffer) == 0)
	{
		remove(IniFile::GetInstance()->GetNmapFilePath().c_str());
	}
#endif // LINUX

	std::stringstream ss;
	ss << "nmap -sP 10.0.0.1-255 -oX " << IniFile::GetInstance()->GetNmapFilePath();
	system(ss.str().c_str());

	std::vector<DetectedPresenceDevice> lastFrameDeviceipAddresses;
	std::swap(m_deviceIpAddresses, lastFrameDeviceipAddresses);

	m_presentDevices = false;
	m_deviceIpAddresses.clear();

	if (ProcessPresenceFile())
		return true;

	return DetectPresenceWithDeviceList(lastFrameDeviceipAddresses);
}

bool PresenceFile::DetectSpecificPresencesWithDevices()
{
	std::lock_guard<std::mutex> autoLock(m_mutex);

	return DetectPresenceWithDeviceList(m_deviceIpAddresses);
}

bool PresenceFile::ProcessPresenceFile()
{
	std::ifstream iniFile;
#ifdef LINUX
	iniFile.open(IniFile::GetInstance()->GetNmapFilePath());
#else
	iniFile.open(R"(D:\huedpd.xml)");
#endif // LINUX

	if (!iniFile.is_open())
	{
		return false;
	}

	int fileSize = ReadFileSize(iniFile);

	std::string fileContents;
	ReadFileContents(iniFile, fileContents, fileSize);

	auto index = fileContents.find("<nmaprun");
	fileContents = fileContents.substr(index);

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError err = doc.Parse(fileContents.c_str());
	if (err != tinyxml2::XML_SUCCESS)
	{
		return false;
	}

	if (tinyxml2::XMLElement* rootElem = doc.FirstChildElement("nmaprun"))
	{
		for (tinyxml2::XMLElement* firstLevelElem = rootElem->FirstChildElement(); firstLevelElem != nullptr; firstLevelElem = firstLevelElem->NextSiblingElement())
		{
			if (firstLevelElem == nullptr)
				continue;

			if (strcmp(firstLevelElem->Name(), "host") != 0)
				continue;

			//Determine the status
			bool isStateUp = false;
			std::vector<DetectedPresenceDevice> deviceIpAddresses;
			for (tinyxml2::XMLElement* hostChildElem = firstLevelElem->FirstChildElement(); hostChildElem != nullptr; hostChildElem = hostChildElem->NextSiblingElement())
			{
				if (strcmp(hostChildElem->Name(), "status") == 0)
				{
					isStateUp = strcmp(hostChildElem->Attribute("state"), "up") == 0;
				}
				else if (strcmp(hostChildElem->Name(), "address") == 0)
				{
					if (strcmp(hostChildElem->Attribute("addrtype"), "ipv4") == 0)
					{
						deviceIpAddresses.push_back(DetectedPresenceDevice(hostChildElem->Attribute("addr")));
					}
				}
				else if (strcmp(hostChildElem->Name(), "hostnames") == 0 && IsPresenceDevice(hostChildElem, isStateUp))
				{
					m_presentDevices = true;
					m_lastPresentDeviceTime = std::chrono::system_clock::now();
					for (const DetectedPresenceDevice& str : deviceIpAddresses)
					{
						m_deviceIpAddresses.push_back(str);
					}
					deviceIpAddresses.clear();
				}
			}
		}
	}

	return m_presentDevices;
}

bool PresenceFile::DetectPresenceWithDeviceList(std::vector<DetectedPresenceDevice>& deviceIpAddresses)
{
	std::stringstream ss;
	for (DetectedPresenceDevice& deviceIpAddress : deviceIpAddresses)
	{
		ss.clear();
		ss << "nmap -sP " << deviceIpAddress.ipAdress << " -oX " << IniFile::GetInstance()->GetNmapFilePath();

		if (ProcessPresenceFile())
			return true;
		else
			++deviceIpAddress.totalCount;
	}

	std::vector<DetectedPresenceDevice> devices;
	std::swap(deviceIpAddresses, devices);

	for (DetectedPresenceDevice& deviceIpAddress : devices)
	{
		if (deviceIpAddress.totalCount < 5)
		{
			deviceIpAddresses.emplace_back(deviceIpAddress);
		}
	}

	return false;
}

int PresenceFile::ReadFileSize(std::ifstream& file)
{
	file.seekg(0, std::ios::end);
	int fileSize = static_cast<int>(file.tellg());
	file.seekg(0, std::ios::beg);
	return fileSize;
}

void PresenceFile::ReadFileContents(std::ifstream& file, std::string& fileContents, int fileSize)
{
	char* pszFileContents = new char[fileSize + 1];
	memset(pszFileContents, 0, fileSize + 1);
	file.read(pszFileContents, fileSize);

	fileContents = { pszFileContents };
	delete[] pszFileContents;
	pszFileContents = nullptr;
}

bool PresenceFile::IsPresenceDevice(tinyxml2::XMLElement* hostnamesElem, bool isStateUp)
{
	std::vector<std::string> hostnames;
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
			return true;
		}
	}

	return false;
}
