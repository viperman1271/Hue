package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueSceneInformation {
    public HueSceneInformation(JSONObject value, String sceneId) {
    id = sceneId;
        try {
            name = value.getString("name");
            owner = value.getString("owner");
            picture = value.getString("picture");
            lastupdated = value.getString("lastupdated");
            version = value.getInt("version");
            recycle = value.getBoolean("recycle");
            locked = value.getBoolean("locked");

            JSONArray array = value.getJSONArray("lights");
            for (int i = 0; i < array.length(); ++i) {
                lights.add(array.getString(i));
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    String id;
    String name;
    List<String> lights;
    String owner;
    String picture;
    String lastupdated;
    int version;
    boolean recycle;
    boolean locked;
}
