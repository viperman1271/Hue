#include <string>

struct HueConfigInformation
{
    HueConfigInformation()
    {}

    HueConfigInformation(const Json::Value& value)
        : zigbeechannel(value.get("zigbeechannel", 0).asInt())
        , proxyport(value.get("proxyport", 0).asInt())
        , dhcppublic(value.get("dhcppublic", false).asBool())
        , linkbutton(value.get("linkbutton", false).asBool())
        , portalservices(value.get("portalservices", false).asBool())
        , factorynew(value.get("factorynew", false).asBool())
        , name(value.get("name", "").asString())
        , bridgeid(value.get("bridgeid", "").asString())
        , mac(value.get("mac", "").asString())
        , ipaddress(value.get("ipaddress", "").asString())
        , netmask(value.get("netmask", "").asString())
        , gateway(value.get("gateway", "").asString())
        , proxyaddress(value.get("proxyaddress", "").asString())
        , UTC(value.get("UTC", "").asString())
        , localtime(value.get("localtime", "").asString())
        , timezone(value.get("timezone", "").asString())
        , modelid(value.get("modelid", "").asString())
        , swversion(value.get("swversion", "").asString())
        , apiversion(value.get("apiversion", "").asString())
        , portalconnection(value.get("portalconnection", "").asString())
    {}

    int zigbeechannel;
    int proxyport;
    bool dhcppublic;
    bool linkbutton;
    bool portalservices;
    bool factorynew;
    std::string name;
    std::string bridgeid;
    std::string mac;
    std::string ipaddress;
    std::string netmask;
    std::string gateway;
    std::string proxyaddress;
    std::string UTC;
    std::string localtime;
    std::string timezone;
    std::string modelid;
    std::string swversion;
    std::string apiversion;
    std::string portalconnection;
};
