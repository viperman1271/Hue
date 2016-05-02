using Hue.ObjectModel;
using Hue.Properties;
using System;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Hue
{
    public class HueBridge
    {
        public UrlProvider Urls;
        //public ConcurrentDictionary<string, HueLight> Lights { get; set; }

        public event EventHandler PushButtonOnBridge;

        public readonly string IP; 

        private readonly string appname = "winhueapp";
        private bool IsAuthenticated = false;

        public HueSystemInformation info;
        
        public HueBridge(string ip)
        {
            Urls = new UrlProvider(ip);
            IP = ip;
            // not needed - clock for every 1 sec update status. 
            //timer = new Timer(StatusCheckEvent, null, 0, 1000);
            InitializeRouter();
        }

        public async Task<bool> InitializeRouter()
        {
            if (!string.IsNullOrEmpty(Settings.Default.BridgeApiKey))
            {
                TryUpdateAllData();
                if (IsAuthenticated)
                {
                    return true;
                }
            }

            return await Register();
        }

        private void StatusCheckEvent(object state)
        {
            // read state of lamps
            if (IsAuthenticated) 
                TryUpdateAllData();
        }

        public void TryUpdateAllData()
        {
            var url = Urls.GetStatusUrl();
            var statusResponse = new HttpClient().GetStringAsync(url).Result;

            HueResponse hueResponse = JsonConvert.DeserializeObject<HueResponse>(statusResponse);

            if (hueResponse.error == null || hueResponse.error.type != 1)
            {
                info = new HueSystemInformation();
                info.DeserializeJson(statusResponse);

                IsAuthenticated = true;
            }
        }

        public void TryUpdateAllRules()
        {
            var url = Urls.GetStatusUrl();
            var statusResponse = new HttpClient().GetStringAsync(url).Result;

            HueResponse hueResponse = JsonConvert.DeserializeObject<HueResponse>(statusResponse);

            if (hueResponse.error == null || hueResponse.error.type != 1 && info != null)
            {
                Newtonsoft.Json.Linq.JObject deserializedData = JsonConvert.DeserializeObject<dynamic>(statusResponse);
                info.UpdateRules(deserializedData);

                IsAuthenticated = true;
            }
        }

        private async Task<bool> Register()
        {
            var retryCount = 0;
            const int retryMax = 60;
            const int pauseMilliseconds = 1000;

            while (retryCount < retryMax) // wait a minute, check each second
            {
                HueRegistration hueRegistration = new HueRegistration(appname, "mike");
                var responseFromServer = await CommUtilities.Post(Urls, hueRegistration);

                //var abc = JsonConvert.DeserializeObject(responseFromServer);
                HueResponse hueResponse = JsonConvert.DeserializeObject<HueResponse>(responseFromServer);

                if (hueResponse.error != null && hueResponse.error.type == 101) //responseFromServer.Contains("link button not pressed")
                {
                    //responseFromServer = "[{\"error\":{\"type\":7,\"address\":\"/username\",\"description\":\"invalid value, winhueapp, for parameter, username\"}},{\"error\":{\"type\":101,\"address\":\"\",\"description\":\"link button not pressed\"}}]"
                    // link button not pressed, inform on first try only
                    if (retryCount == 0 && PushButtonOnBridge != null)
                    {
                        PushButtonOnBridge(this, null);
                    }

                    Thread.Sleep(pauseMilliseconds); // sleep for a second, then retry
                    ++retryCount;
                }
                else if(hueResponse.success != null && !String.IsNullOrWhiteSpace(hueResponse.success.username))
                {
                    Settings.Default.BridgeApiKey = hueResponse.success.username;
                    Settings.Default.Save();
                    
                    IsAuthenticated = true;
                    return true;
                }
            }

            IsAuthenticated = false;
            return false;
        }

        private async void SetLightStatus(string lightKey, string json)
        {
            HttpClient client = new HttpClient();
            HttpContent content = new StringContent(json);
            await client.PutAsync(Urls.GetLampUrl(lightKey), content);
        }

        public void AlertAllLights()
        {
            if (info.lights != null && IsAuthenticated)
            {
                foreach (var light in info.lights)
                {
                    SetLightStatus(light.id, "{\"alert\": \"select\" }");
                }
            }
        }

        public void FlashLights()
        {
            if (info.lights != null && IsAuthenticated)
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
            }
        }

        public void TurnOffLights()
        {
            if (info.lights != null && IsAuthenticated)
            {
                // push PUT request to /api/key/lights/1/state
                foreach (var light in info.lights)
                {
                    SetLightStatus(light.id, "{\"on\": false }");
                    //HueLightState.JsonCommand(new HueLightState{ on = true }, new HueLightState() { on = false }));
                }
            }
        }
    }
}