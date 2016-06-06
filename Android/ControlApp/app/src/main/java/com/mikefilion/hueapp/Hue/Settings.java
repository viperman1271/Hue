package com.mikefilion.hueapp.Hue;

import android.app.Activity;

/**
 * Created by mfilion on 2016-05-02.
 */
public class Settings {
    private String m_bridgeApiKey;
    private HueBridge m_hueBridge;
    private static Settings ms_defaultInstance;

    public static void Configure(Activity activity) {
        if(ms_defaultInstance == null) {
            ms_defaultInstance = new Settings();
            ms_defaultInstance.Load(activity);
        }
    }

    public static Settings GetDefault() {
        return ms_defaultInstance;
    }

    public void Save(Activity activity) {
        activity.getPreferences(2).edit().putString("BridgeApiKey", m_bridgeApiKey);
    }

    private void Load(Activity activity) {
        m_bridgeApiKey = activity.getPreferences(2).getString("BridgeApiKey", "");
    }

    public String GetBridgeApiKey() {
        return m_bridgeApiKey;
    }

    public void SetBridgeApiKey(String bridgeApiKey) {
        m_bridgeApiKey = bridgeApiKey;
    }

    public HueBridge GetHueBridge() {
        return m_hueBridge;
    }

    public void SetHueBridge(HueBridge bridge) {
        m_hueBridge = bridge;
    }
}
