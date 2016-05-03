namespace Hue.ObjectModel
{
    class HueError
    {
        public int type;
        public string address;
        public string description;

        public HueError()
        {
            type = 0;
            address = null;
            description = null;
        }
    }
}
