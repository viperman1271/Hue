#pragma once

#include <string>

class Settings
{
public:
    static Settings* GetInstance();

    const std::string& GetBridgeApiKey() const { return m_key; }
    void SetBridgeApiKey(const std::string& in_key) { m_key = in_key; }

    void Load();
    void Save();
private:
    Settings();

private:
    static Settings* ms_instance;
    std::string m_key;
};