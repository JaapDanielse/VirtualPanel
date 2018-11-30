using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VirtualPanel
{
    public class MessageEventArgs : EventArgs
    {
        public int ChannelID { get; }
        public vp_type Type { get; }
        public object Data { get; }

        public MessageEventArgs(int channel, vp_type type, object data)
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