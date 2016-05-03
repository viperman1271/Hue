package com.mikefilion.hueapp.Hue;

/**
 * Created by mfilion on 2016-05-02.
 */
public class UrlProvider {

    private String ip;

    public UrlProvider(String ip)
    {
        this.ip = ip;

        if (!this.ip.startsWith("http://"))
            this.ip = "http://" + this.ip;

        if(this.ip.endsWith("/")) {
            this.ip = this.ip.substring(0, this.ip.length() - 1);
        }

        this.ip = this.ip.replace("/description.xml", "");
    }

    public String GetStatusUrl()
    {
        return ip + "/api/" + Settings.GetDefault().GetBridgeApiKey();
    }

    public String GetRegisterUrl()
    {
        return ip + "/api";
    }

    public String GetLampUrl(String lightKey)
    {
        return ip + "/api/" + Settings.GetDefault().GetBridgeApiKey() + "/lights/" + lightKey + "/state";
    }

    public String GetRuleUrl(String ruleKey)
    {
        return ip + "/api/" + Settings.GetDefault().GetBridgeApiKey() + "/rules/" + ruleKey + "/";
    }
}
