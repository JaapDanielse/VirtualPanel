using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;

namespace VirtualPanel
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            string preSelectedCOM = "";
            string preSelSpeedString = "";

            if (args.Length > 0)
            {
                var arguments = new Dictionary<string, string>();

                foreach (string argument in args)
                {
                    string[] splitted = argument.Split('=');

                    if (splitted.Length == 2)
                    {
                        arguments[splitted[0]] = splitted[1];
                    }
                }
                if(arguments.ContainsKey("port")) preSelectedCOM = arguments["port"];
                if (arguments.ContainsKey("speed")) preSelSpeedString = arguments["speed"];
            }

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new VirtualPanelForm(preSelectedCOM, preSelSpeedString));
        }
    }
}
