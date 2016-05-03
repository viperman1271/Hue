package com.mikefilion.hueapp.Hue;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.view.View;

import com.mikefilion.hueapp.ObjectModel.HueBridgeInfo;

import org.json.JSONException;
import org.json.JSONObject;

import java.net.HttpURLConnection;
import java.net.URL;

public class HueBridgeLocator extends AsyncTask<Void, Void, HueBridge>{
    private final View mView;

    public HueBridgeLocator(View view) {
        this.mView = view;
    }

    public static HueBridge Locate(View view) {
        ConnectivityManager connMgr = (ConnectivityManager)view.getContext().getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();
        if (networkInfo != null && networkInfo.isConnected()) {
            try {
                return new HueBridgeLocator(view).execute().get();
            } catch (Exception e) {
                e.printStackTrace();
                return null;
            }
        } else {
            // display error
        }

        //https://www.meethue.com/api/nupnpx
        return LocateWithApi(view);
    }

    public static HueBridge LocateWithApi(View view) {
        try {
            String content = CommUtilities.Get("https://www.meethue.com/api/nupnp");
            if(content.startsWith("[")) {
                content = content.substring(1);
            }

            if(content.endsWith("]")) {
                content = content.substring(0, content.length() - 1);
            }

            JSONObject json = new JSONObject(content);

            HueBridgeInfo hueBridgeInfo = new HueBridgeInfo(json);
            return new HueBridge(hueBridgeInfo.internalipaddress, view);
        } catch (JSONException e) {
            e.printStackTrace();
            return null;
        }
    }

    // http://www.nerdblog.com/2012/10/a-day-with-philips-hue.html - description.xml retrieval
    private static boolean IsHue(String discoveryUrl) {
        try {
            URL url = new URL(discoveryUrl);
            HttpURLConnection client = (HttpURLConnection) url.openConnection();
            client.setReadTimeout(2000);
            client.setConnectTimeout(2000);

            String res = client.getContent().toString();
            if (!StringUtils.isNullOrWhitespace(res))
            {
                if (res.contains("Philips hue bridge"))
                    return true;
            }
        } catch(Exception ex)
        {
            return false;
        }
        return false;
    }

    /**
     * Override this method to perform a computation on a background thread. The
     * specified parameters are the parameters passed to {@link #execute}
     * by the caller of this task.
     * <p/>
     * This method can call {@link #publishProgress} to publish updates
     * on the UI thread.
     *
     * @param params The parameters of the task.
     * @return A result, defined by the subclass of this task.
     * @see #onPreExecute()
     * @see #onPostExecute
     * @see #publishProgress
     */
    @Override
    protected HueBridge doInBackground(Void... params) {
        return LocateWithApi(mView);
    }
}
