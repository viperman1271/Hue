using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace Hue.ObjectModel
{
    public class HueSystemInformation
    {
        public readonly List<HueLightInformation> lights;
        public readonly List<HueGroupInformation> groups;
        public readonly List<HueSceneInformation> scenes;
        public readonly List<HueRuleInformation> rules;
        public readonly List<HueSensorInformation> sensors;
        public HueConfigInformation config;

        public HueSystemInformation()
        {
            lights = new List<HueLightInformation>();
            groups = new List<HueGroupInformation>();
            scenes = new List<HueSceneInformation>();
            rules = new List<HueRuleInformation>();
            sensors = new List<HueSensorInformation>();
        }

        public void DeserializeJson(string json)
        {
            try
            {
                Newtonsoft.Json.Linq.JObject deserializedData = JsonConvert.DeserializeObject<dynamic>(json);

                UpdateLights(deserializedData);
                UpdateGroups(deserializedData);
                UpdateConfig(deserializedData);
                UpdateScenes(deserializedData);
                UpdateSensors(deserializedData);
                UpdateRules(deserializedData);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        public void UpdateLights(Newtonsoft.Json.Linq.JObject deserializedData = null)
        {
            lights.Clear();
            foreach (var obj in deserializedData["lights"])
            {
                Newtonsoft.Json.Linq.JProperty properties = (Newtonsoft.Json.Linq.JProperty)obj;
                string jsonData = properties.ToString();
                string id = jsonData.Substring(1, jsonData.IndexOf(':') - 2);
                RemoveQuotationMarks(ref id);
                jsonData = jsonData.Substring(jsonData.IndexOf('{'));
                HueLightInformation lightInfo = JsonConvert.DeserializeObject<HueLightInformation>(jsonData);
                lightInfo.id = id;
                lights.Add(lightInfo);
            }
        }

        public void UpdateGroups(Newtonsoft.Json.Linq.JObject deserializedData = null)
        {
            groups.Clear();
            foreach (var obj in deserializedData["groups"])
            {
                Newtonsoft.Json.Linq.JProperty properties = (Newtonsoft.Json.Linq.JProperty)obj;
                string jsonData = properties.ToString();
                jsonData = jsonData.Substring(jsonData.IndexOf('{'));
                HueGroupInformation groupInfo = JsonConvert.DeserializeObject<HueGroupInformation>(jsonData);
                groups.Add(groupInfo);
            }
        }

        public void UpdateConfig(Newtonsoft.Json.Linq.JObject deserializedData = null)
        {
            var configObj = (Newtonsoft.Json.Linq.JObject)deserializedData["config"];
            config = JsonConvert.DeserializeObject<HueConfigInformation>(configObj.ToString());
        }

        public void UpdateScenes(Newtonsoft.Json.Linq.JObject deserializedData = null)
        {
            scenes.Clear();
            foreach (var scene in deserializedData["scenes"])
            {
                Newtonsoft.Json.Linq.JProperty properties = (Newtonsoft.Json.Linq.JProperty)scene;
                string jsonData = properties.ToString();
                string id = jsonData.Substring(0, jsonData.IndexOf(':'));
                RemoveQuotationMarks(ref id);
                jsonData = jsonData.Substring(jsonData.IndexOf('{'));
                HueSceneInformation sceneInfo = JsonConvert.DeserializeObject<HueSceneInformation>(jsonData);
                sceneInfo.id = id;
                scenes.Add(sceneInfo);
            }
        }

        public void UpdateRules(Newtonsoft.Json.Linq.JObject deserializedData = null)
        {
            rules.Clear();
            foreach (var scene in deserializedData["rules"])
            {
                Newtonsoft.Json.Linq.JProperty properties = (Newtonsoft.Json.Linq.JProperty)scene;
                string jsonData = properties.ToString();
                string id = jsonData.Substring(0, jsonData.IndexOf(':'));
                RemoveQuotationMarks(ref id);
                jsonData = jsonData.Substring(jsonData.IndexOf('{'));
                HueRuleInformation ruleInfo = JsonConvert.DeserializeObject<HueRuleInformation>(jsonData);
                ruleInfo.id = id;
                rules.Add(ruleInfo);
            }
        }

        public void UpdateSensors(Newtonsoft.Json.Linq.JObject deserializedData = null)
        {
            sensors.Clear();
            foreach (var sensor in deserializedData["sensors"])
            {
                Newtonsoft.Json.Linq.JProperty properties = (Newtonsoft.Json.Linq.JProperty)sensor;
                string jsonData = properties.ToString();
                jsonData = jsonData.Substring(jsonData.IndexOf('{'));
                HueSensorInformation sensorInfo = JsonConvert.DeserializeObject<HueSensorInformation>(jsonData);
                sensors.Add(sensorInfo);
            }
        }

        public void RemoveQuotationMarks(ref string str)
        {
            int index = str.IndexOf('\"');
            while (index >= 0)
            {
                str = str.Remove(index, 1);
                index = str.IndexOf('\"');
            }
        }
    }
}
