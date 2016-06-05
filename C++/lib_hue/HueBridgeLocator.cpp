#include "HueBridgeLocator.h"
#include "HueBridge.h"
#include "ObjectModel/HueBridgeInfo.h"
#include "HttpClient.h"
#include <iostream>
#ifdef LINUX_VS
#	include "../lib_curl_linux/include/curl/curl.h"
#else
#	include <curl/curl.h>
#endif
const char* s_pszAddress = "https://www.meethue.com/api/nupnp";

HueBridge* HueBridgeLocator::Locate()
{
    //https://www.meethue.com/api/nupnp
    return LocateWithApi();
}

HueBridge* HueBridgeLocator::LocateAsync()
{
    return nullptr;
}

HueBridge* HueBridgeLocator::LocateWithApi()
{
    HttpClient* client = HttpClient::GetInstance();

    std::string json = client->Get(s_pszAddress);

    if(json.empty())
    {
        std::cerr << "HueBridgeLocator::LocateWithApi: Did not receive any json data" << std::endl;
        return nullptr;
    }

#ifdef VERBOSE_OUTPUT
    std::cout << "JSON:" << std::endl << json << std::endl;
#endif // VERBOSE_OUTPUT

    Json::Value root;
    Json::Reader reader;
    reader.parse(json, root);

    HueBridgeInfo hueBridgeInfo(root);
    return new HueBridge(hueBridgeInfo.internalipaddress);
}

bool HueBridgeLocator::IsHue(const std::string& discoveryUrl)
{
    /*var http = new HttpClient{ Timeout = TimeSpan.FromMilliseconds(2000) };
    try {
        var res = await http.GetStringAsync(discoveryUrl);
        if (!std::string.IsNullOrWhiteSpace(res))
        {
            if (res.Contains("Philips hue bridge"))
                return true;
        }
    }
    catch
    {
        return false;
    }*/
    return false;
}
