using System;
using System.CodeDom;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VirtualPanel
{
    public static class ExtentionMethods
    {
        public static String Right(this String s, int start, int length)
        {
            if (s.Length == 0 || start < 0 || start >= s.Length)
                return "";

            int pos = s.Length - length - start;
            if (pos < 0)
            {
                string temp = s.PadLeft(Math.Abs(pos) + s.Length);
                return temp.Substring(0, length);
            }
            else
                return s.Substring(pos, length);
        }

        public static int Zerox(this int i)
        {
            return 0;
        }

        public static void ThreadAwareRaise<TEventArgs>(this EventHandler<TEventArgs> customEvent, object sender, TEventArgs e) where TEventArgs : EventArgs
        {
            foreach (var handler in customEvent.GetInvocationList().OfType<EventHandler<TEventArgs>>())
            {
                var target = handler.Target as ISynchronizeInvoke;
                if (target != null) target.BeginInvoke(handler, new[] { sender, e });
                else handler.Invoke(sender, e);
            }
        }

        public static string ToLiteral(this String input)
        {
            using (var writer = new StringWriter())
            {
                using (var provider = CodeDomProvider.CreateProvider("CSharp"))
                {
                    provider.GenerateCodeFromExpression(new CodePrimitiveExpression(input), writer, null);
                    return writer.ToString();
                }
            }
        }
    }
}