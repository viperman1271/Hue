package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueRuleInformation {

    public HueRuleInformation(JSONObject value, String ruleId) {
        id = ruleId;
        try {
            name = value.getString("name");
            owner = value.getString("owner");
            created = value.getString("created");
            lasttriggered = value.getString("lasttriggered");
            status = value.getString("status");
            timestriggered = value.getInt("timestriggered");
            recycle = value.getBoolean("recycle");
            JSONArray array = value.getJSONArray("actions");
            for (int i = 0; i < array.length(); ++i) {
                actions.add(new HueRuleAction(array.getJSONObject(i)));
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public final String id;
    public String name;
    public String owner;
    public String created;
    public String lasttriggered;
    public String status;
    public int timestriggered;
    public boolean recycle;
    public List<HueRuleAction> actions;
}
