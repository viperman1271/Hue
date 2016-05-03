package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-02.
 */
public class HueRegistration {
    public String devicetype;

    public HueRegistration(String appname, String client)
    {
        devicetype = appname + "#" + client;
    }

    public String SerializeToJson() {
        JSONObject serializeRoot = new JSONObject();
        try {
            serializeRoot.put("devicetype", devicetype);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return serializeRoot.toString();
    }
}
