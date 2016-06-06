package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueGroupActionInfo {
    HueGroupActionInfo(JSONObject value) {
        try {
            on = value.getBoolean("on");
            bri = value.getInt("bri");
            hue = value.getInt("hue");
            sat = value.getInt("sat");
            ct = value.getInt("ct");
            effect = value.getString("effect");
            alert = value.getString("alert");
            colormode = value.getString("colormode");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    boolean on;
    int bri;
    int hue;
    int sat;
    int ct;
    String effect;
    String alert;
    String colormode;
}
