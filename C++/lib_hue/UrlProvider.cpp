#include "UrlProvider.h"

UrlProvider::UrlProvider(const std::string& in_ip) : ip(in_ip)
{
    if (ip.substr(0, 7) != "http://")
        ip = "http://" + ip;

    if (*ip.end() == '/')
    {
        ip.erase(ip.end(), ip.end());
    }

    int index = ip.find("/description.xml");
    if (index != -1)
    {
        ip = ip.erase(index, 16);
    }
}

std::string UrlProvider::GetStatusUrl()
{
    return ip + "/api/" + Settings::GetInstance()->GetBridgeApiKey();
}

std::string UrlProvider::GetRegisterUrl()
{
    return ip + "/api";
}

std::string UrlProvider::GetLampUrl(const std::string& lightKey)
{
    return ip + "/api/" + Settings::GetInstance()->GetBridgeApiKey() + "/lights/" + lightKey + "/state";
}

std::string UrlProvider::GetRuleUrl(const std::string& ruleKey)
{
    return ip + "/api/" + Settings::GetInstance()->GetBridgeApiKey() + "/rules/" + ruleKey + "/";
}
