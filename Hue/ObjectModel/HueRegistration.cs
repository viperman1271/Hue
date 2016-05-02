using System;

namespace Hue.ObjectModel
{
    class HueRegistration
    {
        public string devicetype;

        public HueRegistration(string appname, string client)
        {
            devicetype = String.Format("{0}#{1}", appname, client);
        }
    }
}
