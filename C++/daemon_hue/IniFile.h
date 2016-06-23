#pragma once

#include <string>

class IniFile
{
	IniFile();

	void ToLower(std::string& str);
public:
	static int Init();
	static IniFile* GetInstance() { return ms_instance; }

    const std::string& GetHttpFilePath() const { return m_httpFile; }
	const std::string& GetNmapFilePath() const { return m_nmapFile; }
	bool GetEnergySaving() const { return m_energySaving; }

	int Load();
private:
	static IniFile* ms_instance;

	std::string m_httpFile;
	std::string m_nmapFile;
	bool m_energySaving;
};

