#pragma once

#include <string>
#include "Settings.h"

class UrlProvider
{
public:
    UrlProvider(const std::string& in_ip);

    std::string GetStatusUrl() const;
    std::string GetRegisterUrl() const;
    std::string GetLampUrl(const std::string& lightKey) const;
    std::string GetRuleUrl(const std::string& ruleKey) const;
private:
    std::string ip;
};
