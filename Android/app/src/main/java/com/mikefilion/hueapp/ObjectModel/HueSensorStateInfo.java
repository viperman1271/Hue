package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueSensorStateInfo {
    public HueSensorStateInfo(JSONObject value) {
        try {
            daylight = value.getBoolean("daylight");
            lastupdated = value.getString("lastupdated");
            buttonevent = value.getInt("buttonevent");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
    public boolean daylight;
    public String lastupdated;
    public int buttonevent;
}
