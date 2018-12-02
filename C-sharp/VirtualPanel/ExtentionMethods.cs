using System;
using System.CodeDom;
using System.CodeDom.Compiler;
using System.ComponentModel;
using System.IO;
using System.Linq;

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