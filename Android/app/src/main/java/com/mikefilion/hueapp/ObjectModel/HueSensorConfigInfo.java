package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueSensorConfigInfo {
    public HueSensorConfigInfo(JSONObject value) {
        try {
            battery = value.getInt("battery");
            on = value.getBoolean("on");
            reachable = value.getBoolean("reachable");
            m_long = value.getString("long");
            lat = value.getString("lat");
            sunriseoffset = value.getString("sunriseoffset");
            sunsetoffset = value.getString("sunsetoffset");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
    int battery;
    boolean on;
    boolean reachable;
    String m_long;
    String lat;
    String sunriseoffset;
    String sunsetoffset;
}
