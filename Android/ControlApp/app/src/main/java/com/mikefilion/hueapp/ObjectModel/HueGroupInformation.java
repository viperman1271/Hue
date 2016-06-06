package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueGroupInformation {
    public HueGroupInformation(JSONObject value) {
        try {
            name = value.getString("name");
            type = value.getString("type");
            action = new HueGroupActionInfo(value.getJSONObject("action"));
            recycle = value.getBoolean("recycle");

            JSONArray array = value.getJSONArray("lights");
            for (int i = 0; i < array.length(); ++i) {
                lights.add(array.getString(i));
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    String name;
    String type;
    List<String> lights;
    HueGroupActionInfo action;
    boolean recycle;
}
