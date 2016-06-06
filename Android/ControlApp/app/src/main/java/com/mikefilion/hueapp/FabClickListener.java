package com.mikefilion.hueapp;

import android.app.Activity;
import android.content.DialogInterface;
import android.view.View;

import com.mikefilion.hueapp.Hue.HueBridge;
import com.mikefilion.hueapp.Hue.HueBridgeLocator;
import com.mikefilion.hueapp.Hue.Settings;

/**
 * Created by mfilion on 2016-05-03.
 */
public class FabClickListener implements View.OnClickListener {
    private final Activity mParentActivity;

    public FabClickListener(Activity parent) {
        mParentActivity = parent;
    }

    /**
     * Called when a view has been clicked.
     *
     * @param view The view that was clicked.
     */
    @Override
    public void onClick(View view) {
        HueBridge bridge = HueBridgeLocator.Locate(view, mParentActivity);
        Settings.GetDefault().SetHueBridge(bridge);
    }
}
