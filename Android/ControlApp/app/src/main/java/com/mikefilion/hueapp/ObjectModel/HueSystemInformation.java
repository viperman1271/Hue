package com.mikefilion.hueapp.ObjectModel;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

/**
 * Created by mfilion on 2016-05-03.
 */
public class HueSystemInformation {
    public void DeserializeJson(JSONObject json) {
        try {
            UpdateLights(json);
            UpdateGroups(json);
            UpdateConfig(json);
            UpdateScenes(json);
            UpdateSensors(json);
            UpdateRules(json);
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public void UpdateLights(JSONObject root) throws JSONException {
        lights.clear();

        JSONArray array = root.getJSONArray("lights");
        for(int i = 0; i < array.length(); ++i) {
            HueLightInformation lightInfo = new HueLightInformation(array.getJSONObject(i), ""/*iter.key().asString()*/);
            lights.add(lightInfo);
        }
    }

    public void UpdateGroups(JSONObject root) throws JSONException {
        groups.clear();

        JSONArray array = root.getJSONArray("groups");
        for(int i = 0; i < array.length(); ++i) {
            HueGroupInformation groupInfo = new HueGroupInformation(array.getJSONObject(i));
            groups.add(groupInfo);
        }
    }

    public void UpdateConfig(JSONObject root) throws JSONException {
        config = new HueConfigInformation(root.getJSONObject("groups"));
    }

    public void UpdateScenes(JSONObject root) throws JSONException {
        scenes.clear();
        JSONArray array = root.getJSONArray("scenes");
        for(int i = 0; i < array.length(); ++i) {
            HueSceneInformation sceneInfo = new HueSceneInformation(array.getJSONObject(i), ""/*iter.key().asString()*/);
            scenes.add(sceneInfo);
        }
    }

    public void UpdateRules(JSONObject root) throws JSONException {
        rules.clear();
        JSONArray array = root.getJSONArray("rules");
        for(int i = 0; i < array.length(); ++i) {
            HueRuleInformation ruleInfo = new HueRuleInformation(array.getJSONObject(i), ""/*iter.key().asString()*/);
            rules.add(ruleInfo);
        }
    }

    public void UpdateSensors(JSONObject root) throws JSONException {
        sensors.clear();
        JSONArray array = root.getJSONArray("sensors");
        for(int i = 0; i < array.length(); ++i) {
            HueSensorInformation sensorInfo = new HueSensorInformation(array.getJSONObject(i));
            sensors.add(sensorInfo);
        }
    }

    public static void RemoveQuotationMarks(String str) {
        int index = str.indexOf('\"');
        while (index >= 0) {
            if(str.endsWith("\"")) {
                str = str.substring(0, index - 1);
            } else {
                str = str.substring(0, index - 1) + str.substring(index + 1);
            }
            index = str.indexOf('\"');
        }
    }

    public List<HueLightInformation> lights;
    public List<HueGroupInformation> groups;
    public List<HueSceneInformation> scenes;
    public List<HueRuleInformation> rules;
    public List<HueSensorInformation> sensors;
    public HueConfigInformation config;
}
