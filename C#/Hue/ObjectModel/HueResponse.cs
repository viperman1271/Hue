namespace Hue.ObjectModel
{
    class HueResponse
    {
        public HueError error;
        public HueUserInfo success;

        public HueResponse()
        {
            error = null;
            success = null;
        }
    }
}
