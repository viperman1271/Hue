using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Hue
{
    class CommUtilities
    {
        public static async Task<string> Post(UrlProvider urls, object data)
        {
            string body = JsonConvert.SerializeObject(data);

            HttpClient client = new HttpClient();
            HttpContent content = new StringContent(body);
            var result = await client.PostAsync(urls.GetRegisterUrl(), content);
            var responseFromServer = await result.Content.ReadAsStringAsync();
            responseFromServer = responseFromServer.TrimStart('[').TrimEnd(']');

            return responseFromServer;
        }
    }
}
