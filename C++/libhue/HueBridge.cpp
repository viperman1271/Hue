#include "HueBridge.h"
#include "ObjectModel/HueError.h"
#include "ObjectModel/HueUserInfo.h"
#include "ObjectModel/HueRegistration.h"
#include "ObjectModel/HueResponse.h"
#include "HttpClient.h"
#include "LibHue.h"
#include <libhue/Platform.h>
#include <iostream>
#ifdef LINUX
#    include <unistd.h>
#endif //LINUX

//Static member initialization
#ifdef LINUX
const std::string HueBridge::appname{ "linuxhueapp" };
#else
const std::string HueBridge::appname{ "winhueapp" };
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
	Json::Value root;

	if (GetStatusJson(root) == 0)
    {
        info.DeserializeJson(root);

        IsAuthenticated = true;
    }
}

void HueBridge::TryUpdateAllRules()
{
	Json::Value root;

	if (GetStatusJson(root) == 0)
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
            SetLightStatus(light.id, R"({ "alert": "select" })");
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
            SetLightStatus(light.id, R"({ "bri": 254, "on": true, "transitiontime":0 })");
        }

		HUEPLATFORM::SLEEP(std::chrono::seconds(1));

        for(auto light : info.lights)
        {
            SetLightStatus(light.id, R"({ "bri": 0, "on": false, "transitiontime":0 })");
        }
    }
}

void HueBridge::TurnOnLights()
{
    if (IsAuthenticated)
    {
        for (auto light : info.lights)
        {
            SetLightStatus(light.id, R"({"bri": 254, "on": true })");
        }
    }
}

void HueBridge::TurnOffLights()
{
    if (IsAuthenticated)
    {
        for(auto light : info.lights)
        {
            SetLightStatus(light.id, R"({"on": false })");
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
                LibHue::RegistationError(hueResponse.error.type);
            }

			HUEPLATFORM::SLEEP(std::chrono::milliseconds(pauseMilliseconds));
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

int HueBridge::GetStatusJson(Json::Value& root) const
{
	std::string url = Urls.GetStatusUrl();
	std::string responseFromServer = HttpClient::GetInstance()->Get(url);

	Json::Reader reader;
	reader.parse(responseFromServer, root);
	HueResponse hueResponse(root);

	return hueResponse.error.type;
}

void HueBridge::SetLightStatus(const std::string& lightKey, const std::string& json) const
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

void HueBridge::TurnOnLight(const HueLightInformation& lightInfo) const
{
	SetLightStatus(lightInfo.id, "{\"bri\": 254, \"on\": true }");
}

void HueBridge::TurnOffLight(const HueLightInformation& lightInfo) const
{
	SetLightStatus(lightInfo.id, "{\"bri\": 0, \"on\": false }");
}