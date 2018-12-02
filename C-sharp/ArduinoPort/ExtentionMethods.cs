using System;
using System.ComponentModel;
using System.Linq;

namespace ArduinoCom
{
    public static class ExtentionMethods
    {
        public static void ThreadAwareRaise<TEventArgs>(this EventHandler<TEventArgs> customEvent, object sender, TEventArgs e) where TEventArgs : EventArgs
        {
            foreach (var handler in customEvent.GetInvocationList().OfType<EventHandler<TEventArgs>>())
            {
                var target = handler.Target as ISynchronizeInvoke;
                if (target != null) target.BeginInvoke(handler, new[] { sender, e });
                else handler.Invoke(sender, e);
            }
        }
    }
}