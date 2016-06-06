package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-02.
 */
public class HueResponse {
    public HueError error;
    public HueUserInfo success;

    public HueResponse(JSONObject json) {
        try {
            error = new HueError((JSONObject)json.get("error"));
        } catch (JSONException e) {
            e.printStackTrace();
        }
        try {

            if(error == null) {
                success = new HueUserInfo((JSONObject) json.get("success"));
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
}
