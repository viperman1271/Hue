package com.mikefilion.hueclientapp;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;

public class WifiConnectionBroadcastReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        ConnectivityManager cm = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo activeNetwork  = cm.getActiveNetworkInfo();
        if (activeNetwork  != null) {
            if (activeNetwork.isConnected() && activeNetwork.getType() == ConnectivityManager.TYPE_WIFI) {
                WifiManager wifiMgr = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);
                WifiInfo wifiInfo = wifiMgr.getConnectionInfo();
                String name = wifiInfo.getSSID();
                if(name == "mfwf" || name.contains("mfwf_")) {

                }
            }
        }
    }
}
