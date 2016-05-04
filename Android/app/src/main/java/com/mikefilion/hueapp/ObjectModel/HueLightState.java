package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueLightState {
    public HueLightState(JSONObject value) {
        try {
            on = value.getBoolean("on");
            reachable = value.getBoolean("reachable");
            bri = value.getInt("bri");
            hue = value.getInt("hue");
            sat = value.getInt("sat");
            cy = value.getInt("cy");
            effect = value.getString("effect");
            alert = value.getString("alert");
            colormode = value.getString("colormode");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    boolean on;
    boolean reachable;
    int bri;
    int hue;
    int sat;
    int cy;
    String effect;
    String alert;
    String colormode;
}