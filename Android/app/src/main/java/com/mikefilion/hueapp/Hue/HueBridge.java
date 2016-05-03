package com.mikefilion.hueapp.Hue;

import android.support.design.widget.Snackbar;
import android.view.View;
import android.widget.Toast;

import com.mikefilion.hueapp.ObjectModel.HueRegistration;
import com.mikefilion.hueapp.ObjectModel.HueResponse;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by mfilion on 2016-05-02.
 */
public class HueBridge {

    public UrlProvider Urls;
    public final String IP;

    private final String appname = "androidhueapp";
    private boolean IsAuthenticated = false;

    public HueBridge(String ip, View view) {
        Urls = new UrlProvider(ip);
        IP = ip;

        InitializeRouter(view);
    }

    public boolean InitializeRouter(View view) {
        String bridgeApiKey = Settings.GetDefault().GetBridgeApiKey();
        if (bridgeApiKey != null && !bridgeApiKey.isEmpty())
        {
            TryUpdateAllData();
            if (IsAuthenticated)
            {
                return true;
            }
        }

        if(!Register(view)) {
            return false;
        }

        TryUpdateAllData();
        return true;
    }

    private void StatusCheckEvent(Object state)
    {
        // read state of lamps
        if (IsAuthenticated)
            TryUpdateAllData();
    }

    public void TryUpdateAllData() {
        /*String url = Urls.GetStatusUrl();
        String statusResponse = new HttpClient().GetStringAsync(url).Result;

        HueResponse hueResponse = JsonConvert.DeserializeObject<HueResponse>(statusResponse);

        if (hueResponse.error == null || hueResponse.error.type != 1)
        {
            info = new HueSystemInformation();
            info.DeserializeJson(statusResponse);

            IsAuthenticated = true;
        }*/
    }

    public void TryUpdateAllRules() {
        /*var url = Urls.GetStatusUrl();
        var statusResponse = new HttpClient().GetStringAsync(url).Result;

        HueResponse hueResponse = JsonConvert.DeserializeObject<HueResponse>(statusResponse);

        if (hueResponse.error == null || hueResponse.error.type != 1 && info != null)
        {
            Newtonsoft.Json.Linq.JObject deserializedData = JsonConvert.DeserializeObject<dynamic>(statusResponse);
            info.UpdateRules(deserializedData);

            IsAuthenticated = true;
        }*/
    }

    private boolean Register(View view)  {
        try {
            int retryCount = 0;
            final int retryMax = 60;
            final int pauseMilliseconds = 1000;

            HueRegistration hueRegistration = new HueRegistration(appname, "mike");
            String serializedHueRegistration = hueRegistration.SerializeToJson();

            while (retryCount < retryMax) {
                String responseFromServer = CommUtilities.Post(Urls, serializedHueRegistration);

                if(responseFromServer.startsWith("[")) {
                    responseFromServer = responseFromServer.substring(1);
                }

                if(responseFromServer.endsWith("]")) {
                    responseFromServer = responseFromServer.substring(0, responseFromServer.length() - 1);
                }

                JSONObject json = new JSONObject(responseFromServer);
                HueResponse hueResponse = new HueResponse(json);

                if (hueResponse.error != null && hueResponse.error.type == 101) //responseFromServer.Contains("link button not pressed")
                {
                    //responseFromServer = "[{\"error\":{\"type\":7,\"address\":\"/username\",\"description\":\"invalid value, winhueapp, for parameter, username\"}},{\"error\":{\"type\":101,\"address\":\"\",\"description\":\"link button not pressed\"}}]"
                    // link button not pressed, inform on first try only
                    if (retryCount == 0 /*&& PushButtonOnBridge != null*/)
                    {
                        //PushButtonOnBridge(this, null);
                        Snackbar.make(view, "Link button not pressed", Snackbar.LENGTH_LONG).setAction("Action", null).show();
                    }

                    Thread.sleep(pauseMilliseconds); // sleep for a second, then retry
                    ++retryCount;
                }
                else if(hueResponse.success != null && !StringUtils.isNullOrWhitespace(hueResponse.success.username))
                {
                    Snackbar.make(view, "Bridge connected", Snackbar.LENGTH_LONG).setAction("Action", null).show();

                    Settings.GetDefault().SetBridgeApiKey(hueResponse.success.username);
                    Settings.GetDefault().Save();

                    IsAuthenticated = true;
                    return true;
                }
            }
        } catch (JSONException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        IsAuthenticated = false;
        return false;
    }

    private void SetLightStatus(String lightKey, String json) {
        /*HttpClient client = new HttpClient();
        HttpContent content = new StringContent(json);
        await client.PutAsync(Urls.GetLampUrl(lightKey), content);*/
    }

    public void AlertAllLights() {
        /*if (info.lights != null && IsAuthenticated)
        {
            foreach (var light in info.lights)
            {
                SetLightStatus(light.id, "{\"alert\": \"select\" }");
            }
        }*/
    }

    public void FlashLights() {
        /*if (info.lights != null && IsAuthenticated)
        {
            foreach (var light in info.lights)
            {
                SetLightStatus(light.id, "{\"bri\": 254, \"on\": true }");
            }
            Thread.Sleep(1000);
            foreach (var light in info.lights)
            {
                SetLightStatus(light.id, "{\"bri\": 0, \"on\": false }");
            }
        }*/
    }

    public void TurnOffLights() {
        /*if (info.lights != null && IsAuthenticated)
        {
            // push PUT request to /api/key/lights/1/state
            foreach (var light in info.lights)
            {
                SetLightStatus(light.id, "{\"on\": false }");
                //HueLightState.JsonCommand(new HueLightState{ on = true }, new HueLightState() { on = false }));
            }
        }*/
    }
}