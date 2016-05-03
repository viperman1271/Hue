package com.mikefilion.hueapp.Hue;

/**
 * Created by mfilion on 2016-05-02.
 */
public class Settings {
    private String m_bridgeApiKey;
    private static Settings ms_defaultInstance;

    public static Settings GetDefault() {
        if(ms_defaultInstance == null) {
            ms_defaultInstance = new Settings();
            ms_defaultInstance.Load();
        }
        return ms_defaultInstance;
    }

    public String GetBridgeApiKey() {
        return m_bridgeApiKey;
    }

    public void Save() {

    }

    private void Load() {

    }

    public void SetBridgeApiKey(String bridgeApiKey) {
        m_bridgeApiKey = bridgeApiKey;
    }
}
