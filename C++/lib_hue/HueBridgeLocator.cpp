#include "HueBridgeLocator.h"
#include "HueBridge.h"
#include "ObjectModel/HueBridgeInfo.h"
#include "HttpClient.h"

#include <curl/curl.h>

HueBridge* HueBridgeLocator::Locate()
{
    //https://www.meethue.com/api/nupnp
    return LocateWithApi();
}

HueBridge* HueBridgeLocator::LocateAsync()
{
    /*if (UPnP.NAT.Discover())
    {
        var endpoints = UPnP.NAT.DiscoveredEndpoints
            .Where(s = > s.EndsWith("/description.xml")).ToList();
        foreach(var endpoint in endpoints)
        {
            if (await IsHue(endpoint))
            {
                var ip = endpoint.Replace("http://", "").Replace("/description.xml", "");
                return new HueBridge(ip);
            }
        }
        return null;
    }
    return null;*/
    return nullptr;
}

HueBridge* HueBridgeLocator::LocateWithApi()
{
    HttpClient* client = HttpClient::GetInstance();
    std::string json = client->Get("https://www.meethue.com/api/nupnp");

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
