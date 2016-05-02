#include <string>
#include "Settings.h"

class UrlProvider
{
public:
    UrlProvider(const std::string& in_ip);

    std::string GetStatusUrl();
    std::string GetRegisterUrl();
    std::string GetLampUrl(const std::string& lightKey);
    std::string GetRuleUrl(const std::string& ruleKey);
private:
    std::string ip;
};
