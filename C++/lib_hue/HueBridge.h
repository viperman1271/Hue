#pragma once

#include <string>

#include "UrlProvider.h"
#include "ObjectModel/HueSystemInformation.h"

class HueBridge
{
public:
           
    HueBridge(const std::string& ip)
        : Urls(ip)
	, IP(ip)
	, IsAuthenticated(false)
    {
        InitializeRouter();
    }

    bool InitializeRouter();

    void TryUpdateAllData();
    void TryUpdateAllRules();
    void AlertAllLights();
    void FlashLights();
    void TurnOnLights();
    void TurnOffLights();
    bool IsAfterSunset() const;

	void TurnOnLight(const HueLightInformation& lightInfo) const;
	void TurnOffLight(const HueLightInformation& lightInfo) const;

private:
    bool Register();

    void SetLightStatus(const std::string& lightKey, const std::string& json) const;
public:
    UrlProvider Urls;
    const std::string IP;
    HueSystemInformation info;

private:
    const static std::string appname;
    bool IsAuthenticated;
};
