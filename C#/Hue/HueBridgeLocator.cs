using System;
using System.Linq;
using System.Net.Http;
using System.Threading.Tasks;
using Hue.ObjectModel;
using Newtonsoft.Json;

namespace Hue
{
    /// <summary>
    /// Locates the Philips Hue lights bridge using SSDP 
    /// </summary>
    public static class HueBridgeLocator
    {
        public static HueBridge Locate()
        {
            //https://www.meethue.com/api/nupnp
            return LocateWithApi().Result;
        }

        public static async Task<HueBridge> LocateAsync()
        {
            if (UPnP.NAT.Discover())
            {
                var endpoints = UPnP.NAT.DiscoveredEndpoints
                    .Where(s => s.EndsWith("/description.xml")).ToList();
                foreach (var endpoint in endpoints)
                {
                    if (await IsHue(endpoint))
                    {
                        var ip = endpoint.Replace("http://", "").Replace("/description.xml", "");
                        return new HueBridge(ip);
                    }
                }
                return null;
            }
            return null;
        }

        public static async Task<HueBridge> LocateWithApi()
        {
            HttpClient client = new HttpClient();
            var result = await client.GetAsync(new Uri("https://www.meethue.com/api/nupnp"));

            string content = result.Content.ReadAsStringAsync().Result.TrimStart('[').TrimEnd(']');

            HueBridgeInfo hueBridgeInfo = JsonConvert.DeserializeObject<HueBridgeInfo>(content);
            return new HueBridge(hueBridgeInfo.internalipaddress);
        }


        // http://www.nerdblog.com/2012/10/a-day-with-philips-hue.html - description.xml retrieval
        private static async Task<bool> IsHue(string discoveryUrl)
        {
            var http = new HttpClient {Timeout = TimeSpan.FromMilliseconds(2000)};
            try {
                var res = await http.GetStringAsync(discoveryUrl);
                if (!string.IsNullOrWhiteSpace(res))
                {
                    if (res.Contains("Philips hue bridge"))
                        return true;
                }
            } catch
            {
                return false;
            }
            return false;
        }
    }
}
