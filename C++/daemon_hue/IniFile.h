#pragma once

#include <string>

class IniFile
{
	IniFile();

	void ToLower(std::string& str);
public:
	static int Init();
	static IniFile* GetInstance() { return ms_instance; }

	int Load();
private:
	static IniFile* ms_instance;

	std::string m_httpFile;
};

