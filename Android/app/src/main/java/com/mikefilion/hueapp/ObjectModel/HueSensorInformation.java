package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueSensorInformation {
    public HueSensorInformation(JSONObject value) {
        try {
            state = new HueSensorStateInfo(value.getJSONObject("state"));
            config = new HueSensorConfigInfo(value.getJSONObject("config"));
            name = value.getString("name");
            type = value.getString("type");
            modelid = value.getString("modelid");
            manufacturername = value.getString("manufacturername");
            swversion = value.getString("swversion");
            uniqueid = value.getString("uniqueid");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
    HueSensorStateInfo state;
    HueSensorConfigInfo config;
    String name;
    String type;
    String modelid;
    String manufacturername;
    String swversion;
    String uniqueid;
}
