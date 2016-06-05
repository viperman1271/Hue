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

private:
    bool Register();

    void SetLightStatus(std::string lightKey, std::string json);
public:
    UrlProvider Urls;
    const std::string IP;
    HueSystemInformation info;

private:
    const static std::string appname;
    bool IsAuthenticated;
};
