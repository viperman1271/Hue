#include "HueBridge.h"
#include "ObjectModel/HueError.h"
#include "ObjectModel/HueUserInfo.h"
#include "ObjectModel/HueRegistration.h"
#include "ObjectModel/HueResponse.h"
#include "HttpClient.h"
#include "Callbacks.h"
#include "Platform.h"
#include <iostream>
#ifdef LINUX
#    include <unistd.h>
#endif //LINUX

//Static member initialization
#ifdef LINUX
const std::string HueBridge::appname = "linuxhueapp";
#else
const std::string HueBridge::appname = "winhueapp";
#endif

bool HueBridge::InitializeRouter()
{
    if (Settings::GetInstance()->GetBridgeApiKey().length() > 0)
    {
        TryUpdateAllData();
        if (IsAuthenticated)
        {
            return true;
        }
    }

    return Register();
}

void HueBridge::TryUpdateAllData()
{
    std::string url = Urls.GetStatusUrl();
    std::string responseFromServer = HttpClient::GetInstance()->Get(url);

    Json::Value root;
    Json::Reader reader;
    reader.parse(responseFromServer, root);
    HueResponse hueResponse(root);

    if (hueResponse.error.type == 0)
    {
        info.DeserializeJson(root);

        IsAuthenticated = true;
    }
}

void HueBridge::TryUpdateAllRules()
{
    std::string url = Urls.GetStatusUrl();
    std::string responseFromServer = HttpClient::GetInstance()->Get(url);

    Json::Value root;
    Json::Reader reader;
    reader.parse(responseFromServer, root);
    HueResponse hueResponse(root);

    if (hueResponse.error.type == 0)
    {
        info.DeserializeJson(root);
    }
}

void HueBridge::AlertAllLights()
{
    if (IsAuthenticated)
    {
        for(auto light : info.lights)
        {
            SetLightStatus(light.id, "{\"alert\": \"select\" }");
        }
    }
}

void HueBridge::FlashLights()
{
#ifdef VERBOSE_OUTPUT
	std::cout<<"HueBridge::FlashLights"<<std::endl;
#endif

    if (info.lights.size() > 0 && IsAuthenticated)
    {
        for(auto light : info.lights)
        {
            SetLightStatus(light.id, "{\"bri\": 254, \"on\": true }");
        }

		HUEPLATFORM::SLEEP(1000);

        for(auto light : info.lights)
        {
            SetLightStatus(light.id, "{\"bri\": 0, \"on\": false }");
        }
    }
}

void HueBridge::TurnOnLights()
{
    if (IsAuthenticated)
    {
        for (auto light : info.lights)
        {
            SetLightStatus(light.id, "{\"bri\": 254, \"on\": true }");
        }
    }
}

void HueBridge::TurnOffLights()
{
    if (IsAuthenticated)
    {
        for(auto light : info.lights)
        {
            SetLightStatus(light.id, "{\"on\": false }");
        }
    }
}

bool HueBridge::Register()
{
    int retryCount = 0;
    const int retryMax = 60;
    const int pauseMilliseconds = 1000;

    while (retryCount < retryMax) // wait a minute, check each second
    {
        HueRegistration hueRegistration(appname, "mike");
        auto responseFromServer = HttpClient::GetInstance()->Post(Urls.GetRegisterUrl(), hueRegistration.SerializeText());

        Json::Value root;
        Json::Reader reader;
        reader.parse(responseFromServer, root);
        HueResponse hueResponse(root);

        if (hueResponse.error.type == 101)
        {
            // link button not pressed, inform on first try only
            if (retryCount == 0)
            {
                libhue_callbacks::RegistationError(hueResponse.error.type);
            }

			HUEPLATFORM::SLEEP(pauseMilliseconds);
            ++retryCount;
        }
        else if (!hueResponse.success.username.empty())
        {
            Settings::GetInstance()->SetBridgeApiKey(hueResponse.success.username);
            Settings::GetInstance()->Save();

            IsAuthenticated = true;
            return true;
        }
    }

    IsAuthenticated = false;
    return false;
}

void HueBridge::SetLightStatus(std::string lightKey, std::string json)
{
    HttpClient::GetInstance()->Put(Urls.GetLampUrl(lightKey), json);
}

bool HueBridge::IsAfterSunset() const
{
    for (auto sensor : info.sensors)
    {
        if (sensor.name == "Daylight")
        {
            return !sensor.state.daylight;
        }
    }
    return false;
}
