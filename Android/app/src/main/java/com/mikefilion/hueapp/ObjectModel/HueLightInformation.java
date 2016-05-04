package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueLightInformation {
    public HueLightInformation(JSONObject value, String objectId) {
        id = objectId;
        try {
            state = new HueLightState(value.getJSONObject("state"));
            type = value.getString("type");
            name = value.getString("name");
            modelid = value.getString("modelid");
            manufacturername = value.getString("manufacturername");
            uniqueid = value.getString("uniqueid");
            swversion = value.getString("swversion");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    HueLightState state;
    String type;
    String name;
    String modelid;
    String manufacturername;
    String uniqueid;
    String swversion;
    String id;
}
