#include "IniFile.h"

#include <string.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cctype>

IniFile* IniFile::ms_instance = nullptr;

IniFile::IniFile()
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
	iniFile.open("/etc/hued.conf");
	if (!iniFile.is_open())
	{
		std::cerr << "Couldn't open configuration file for hued";
		return -1;
	}

	iniFile.seekg(0, std::ios::end);
	int fileSize = static_cast<int>(iniFile.tellg());
	iniFile.seekg(0, std::ios::beg);

	char* pszFileContents = new char[fileSize+1];
	iniFile.read(pszFileContents, fileSize);
	pszFileContents[fileSize + 1] = '\0';

	std::string fileContents{ pszFileContents };

	delete [] pszFileContents;
	pszFileContents = nullptr;

	std::stringstream ss;
	ss << std::endl;
	int index = 0;
	while (auto findIndex = fileContents.find(ss.str(), index))
	{
		if (findIndex == std::string::npos)
			break;

		std::string line = fileContents.substr(index, findIndex - index);
		if (line[0] != '#')
		{
			if (auto valueAssignment = fileContents.find('=', index))
			{
				if (valueAssignment != std::string::npos)
				{
					std::string key = fileContents.substr(index, valueAssignment - index);
					std::string value = fileContents.substr(valueAssignment + 1, findIndex - valueAssignment - 1);

					std::cout << "Key: " << key << ", Value: " << value << std::endl;
					
					static const std::string HttpFileString("HttpFile");
					ToLower(key);
					if (key == HttpFileString)
					{
						m_httpFile = value;
					}
				}
			}
		}
		index = findIndex+1;
	}

	iniFile.close();
	return 0;
}