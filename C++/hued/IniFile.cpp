#include "IniFile.h"

#ifdef WINDOWS
#include "Shlobj.h"
#endif

#include <string.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cctype>

IniFile* IniFile::ms_instance = nullptr;

IniFile::IniFile()
	: m_nmapFile("/var/local/hue.xml")
	, m_energySaving(true)
{

}

void IniFile::ToLower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), [](char chr) { return std::tolower(chr); });
}

int IniFile::Init()
{
	ms_instance = new IniFile();
	return ms_instance->Load();
}

int IniFile::Load()
{
	std::ifstream iniFile;
#ifdef LINUX
	iniFile.open("/etc/hued.conf");
#else
    char pszPath[MAX_PATH];
	memset(pszPath, 0, MAX_PATH);
    SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, pszPath);
    int pathLength = strlen(pszPath);
    sprintf_s(pszPath + pathLength, MAX_PATH - pathLength - 1, "%s", "\\hued.conf");
    iniFile.open(pszPath);
#endif
	if (!iniFile.is_open())
	{
		std::cerr << "Couldn't open configuration file for hued";
		return -1;
	}

	iniFile.seekg(0, std::ios::end);
	int fileSize = static_cast<int>(iniFile.tellg());
	iniFile.seekg(0, std::ios::beg);

	char* pszFileContents = new char[fileSize+1];
    memset(pszFileContents, 0, fileSize + 1);
	iniFile.read(pszFileContents, fileSize);

	std::string fileContents{ pszFileContents };

	delete [] pszFileContents;
	pszFileContents = nullptr;

	std::stringstream ss;
	ss << std::endl;
	unsigned int index = 0;
	while (auto findIndex = fileContents.find(ss.str(), index))
	{
        std::string line;
        if (findIndex == std::string::npos)
        {
            line = fileContents.substr(index);
            findIndex = fileContents.size();
        }
        else
        {
            line = fileContents.substr(index, findIndex - index);
        }
		if (line[0] != '#')
		{
			if (auto valueAssignment = fileContents.find('=', index))
			{
				if (valueAssignment != std::string::npos)
				{
					std::string key = fileContents.substr(index, valueAssignment - index);
					std::string value = fileContents.substr(valueAssignment + 1, findIndex - valueAssignment - 1);

					std::cout << "Key: " << key << ", Value: " << value << std::endl;

					static const std::string HttpFileString{ "file" };
					static const std::string NmapFileString{ "nmap" };
					static const std::string EnergySavingString{ "energysaving" };
					ToLower(key);
					if (key == HttpFileString)
					{
						m_httpFile = value;
					}
					else if (key == NmapFileString)
					{
						m_nmapFile = value;
					}
					else if (key == EnergySavingString)
					{
						ToLower(value);
						if (value == "true")
							m_energySaving = true;
						else
							m_energySaving = false;
					}
				}
			}
		}
		index = findIndex + 1;

        if (index >= fileContents.size())
            break;
	}

	iniFile.close();
	return 0;
}