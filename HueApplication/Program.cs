using System;
using System.Linq;
using System.Net.Http;
using Hue;
using Hue.ObjectModel;
using Newtonsoft.Json;

namespace HueApplication
{
    class Program
    {
        static void Main(string[] args)
        {
            HueBridge bridge = HueBridgeLocator.Locate();
            if (bridge == null)
            {
                Console.WriteLine("Bridge was not found.");
            }
            else
            {
                Console.WriteLine("Bridge found at {0}", bridge.IP);
                bridge.PushButtonOnBridge += bridge_PushButtonOnBridge;
                
                //bridge.FlashLights();

                SwitchSceneForLight(bridge);
            }

            Console.ReadKey();
        }

        static void bridge_PushButtonOnBridge(object sender, EventArgs e)
        {
            Console.WriteLine("Please press the button on the bridge to register the application in the next minute.");
        }

        static void SwitchSceneForLight(HueBridge bridge)
        {
            //Find the scene
            HueSceneInformation sceneDay = bridge.info.scenes.FirstOrDefault(n => n.name.Contains("Bathroom - Daytime on "));
            HueSceneInformation sceneNight = bridge.info.scenes.FirstOrDefault(n => n.name.Contains("Bathroom - Night on "));

            if (sceneDay == null || sceneNight == null)
                return;

            foreach (HueRuleInformation rule in bridge.info.rules)
            {
                if (rule.actions.First().body.scene == "7f8303912-on-0")
                {
                    SwitchScene(bridge, rule, sceneDay, sceneNight);
                    Console.WriteLine("Changed to Night");
                }
                else if (rule.actions.First().body.scene == sceneNight.id)
                {
                    SwitchScene(bridge, rule, sceneNight, sceneDay);
                    Console.WriteLine("Changed to Day");
                }
            }
        }

        static void SwitchScene(HueBridge bridge, HueRuleInformation rule, HueSceneInformation originalScene, HueSceneInformation newScene)
        {
            string currentRuleName = originalScene.name.Substring(0, originalScene.name.IndexOf(' '));
            string newRuleName = newScene.name.Substring(0, newScene.name.IndexOf(' '));
            rule.name = rule.name.Replace(currentRuleName, newRuleName);
            rule.actions.First().body.scene = newScene.id;
            HueBasicRuleInformation basicRule = new HueBasicRuleInformation(rule);
            string serializedData = JsonConvert.SerializeObject(basicRule);

            var url = bridge.Urls.GetRuleUrl(rule.id);
            HttpContent content = new StringContent(serializedData);
            var statusResponse = new HttpClient().PutAsync(url, content).Result;
        }
    }
}
