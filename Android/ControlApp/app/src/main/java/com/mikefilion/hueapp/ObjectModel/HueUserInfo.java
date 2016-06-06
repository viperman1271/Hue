package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-02.
 */
public class HueUserInfo {
    public String username;

    public HueUserInfo(JSONObject root)
    {
        try {
            username = root.getString("username");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
}
