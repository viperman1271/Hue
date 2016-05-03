using System.Net.Mail;

namespace Hue.ObjectModel
{
    public class HueRuleInformation
    {
        public string id;
        public string name;
        public string owner;
        public string created;
        public string lasttriggered;
        public int timestriggered;
        public string status;
        public bool recycle;
        public HueRuleAction[] actions;
    }

    public class HueBasicRuleInformation
    {
        public string name;
        public HueRuleAction[] actions;

        public HueBasicRuleInformation(HueRuleInformation ruleInfo)
        {
            name = ruleInfo.name;
            actions = ruleInfo.actions;
        }
    }
}
