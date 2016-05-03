package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-02.
 */
public class HueError {
    public int type;
    public String address;
    public String description;

    public HueError()
    {
        type = 0;
    }

    public HueError(JSONObject json) {
        try {
            type = json.getInt("type");
            address = json.getString("address");
            description = json.getString("description");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
}
