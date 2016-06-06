package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueRuleAction {
    public HueRuleAction(JSONObject value) {
        try {
            address = value.getString("address");
            method = value.getString("method");
            body = new HueRuleActionBody(value.getJSONObject("body"));
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    JSONObject SerializeToJson() {
        JSONObject root = new JSONObject();
        try {
            root.put("address", address);
            root.put("method", method);
            root.put("body", body.SerializeToJson());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return root;
    }

    String address;
    String method;
    HueRuleActionBody body;
}
