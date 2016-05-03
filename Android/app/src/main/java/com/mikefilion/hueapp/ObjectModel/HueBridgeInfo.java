package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-02.
 */
public class HueBridgeInfo {
    public String id;
    public String internalipaddress;

    public HueBridgeInfo(JSONObject json) {
        try {
            id = json.getString("id");
            internalipaddress = json.getString("internalipaddress");
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }
}
