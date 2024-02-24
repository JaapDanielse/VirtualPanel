using System;

namespace ArduinoCom
{
    public class MessageEventArgs<T> : EventArgs
    {
        public int ChannelID { get; }
        public vp_type Type { get; }
        public T Data { get; }

        public MessageEventArgs(int channel, vp_type type, T data)
        {
            ChannelID = channel;
            Type = type;
            Data = data;
        }
    }

    public class ConnectedEventArgs : EventArgs
    {
        public string Portname { get; }

        public ConnectedEventArgs(string Portname)
        {
            this.Portname = Portname;
        }
    }
}