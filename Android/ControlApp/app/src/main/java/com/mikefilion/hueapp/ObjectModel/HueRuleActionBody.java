package com.mikefilion.hueapp.ObjectModel;

import android.renderscript.Sampler;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueRuleActionBody {
    public HueRuleActionBody(JSONObject value) {
        try {
            scene = value.getString("scene");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    JSONObject SerializeToJson()
    {
        JSONObject root = new JSONObject();
        try {
            root.put("scene", scene);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return root;
    }

    String scene;
}
