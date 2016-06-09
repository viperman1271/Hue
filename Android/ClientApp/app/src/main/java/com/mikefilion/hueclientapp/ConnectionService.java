package com.mikefilion.hueclientapp;

import android.app.IntentService;
import android.content.Intent;

public class ConnectionService extends IntentService {

    private BluetoothConnectionBroadcastReceiver m_bluetoothConnectionReceiver;
    private WifiConnectionBroadcastReceiver m_wifiConnectionReceiver;

    public ConnectionService() {
        super("ConnectionService");
    }

    @Override
    public void onCreate() {
        m_wifiConnectionReceiver = new WifiConnectionBroadcastReceiver();
        m_bluetoothConnectionReceiver = new BluetoothConnectionBroadcastReceiver();
    }

    @Override
    protected void onHandleIntent(Intent intent) {
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        return START_STICKY;
    }
}
