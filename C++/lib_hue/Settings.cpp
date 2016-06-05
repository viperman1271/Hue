#include "Settings.h"

#include <json/reader.h>
#include <json/writer.h>

#include <fstream>

#ifdef LINUX
#	include <string.h>
#endif

Settings* Settings::ms_instance = nullptr;

Settings* Settings::GetInstance()
{
    if (ms_instance == nullptr)
    {
        ms_instance = new Settings();
    }
    return ms_instance;
}

Settings::Settings()
{
    Load();
}

void Settings::Load()
{
    std::ifstream file;
#ifdef LINUX
	file.open("/etc/hueappinfo.json");
#else
    file.open("hueappinfo.json");
#endif
    if (file.is_open())
    {
        char dataBuffer[4096];
        memset(dataBuffer, 0, 4096);
        file.read(dataBuffer, 4095);

        Json::Reader reader;
        Json::Value root;
        if (reader.parse(dataBuffer, root))
        {
            m_key = root.get("BridgeApiKey", "").asString();
        }

        file.close();
    }
}

void Settings::Save()
{
    std::ofstream file;
#ifdef LINUX
	file.open("/etc/hueappinfo.json");
#else
	file.open("hueappinfo.json");
#endif
    if (file.is_open())
    {
        Json::FastWriter writer;
        Json::Value root;
        root["BridgeApiKey"] = m_key;
        file << writer.write(root);

        file.close();
    }
}
