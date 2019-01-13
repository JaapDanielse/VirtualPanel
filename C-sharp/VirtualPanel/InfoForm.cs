using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ArduinoCom;

namespace VirtualPanel
{
    public partial class InfoForm : Form
    {
        private ArduinoPort arduinoport;


        public InfoForm(ArduinoPort port)
        {
            arduinoport = port;
            InitializeComponent();
            arduinoport.MessageReceived += Arduinoport_MessageReceived;

        }

        private void Arduinoport_MessageReceived(object sender, MessageEventArgs<object> mse)
        {

            if ((ChannelId)mse.ChannelID == ChannelId.Info && mse.Type == vp_type.vp_string)
            {
                if ((string)mse.Data == "$CLEAR")
                {
                    InfoTextBox.Text = "";
                    InfoLabel.Text = "";
                }
            }

           if ((ChannelId)mse.ChannelID == ChannelId.InfoLabel && mse.Type == vp_type.vp_string)
            {
                InfoLabel.Text = ((string)mse.Data);
                InfoTextBox.Text="";
            }
            if ((ChannelId)mse.ChannelID == ChannelId.InfoText && mse.Type == vp_type.vp_string) InfoTextBox.AppendText(((string)mse.Data) + "\n");
        }

        private void InfoForm_Load(object sender, EventArgs e)
        {
            InfoTextBox.AppendText("Arduino Experiment controlpanel\n\n");
            InfoTextBox.AppendText("Functional design: Jaap Daniëlse\n");
            InfoTextBox.AppendText("Application design and development:\n Jaap, Tim, and Paul Daniëlse\n\n");
            InfoTextBox.AppendText("\u00A9 J.C. Daniëlse 2018\r\n");
        }

        private void InfoForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Visible = false;
            e.Cancel = true;
        }
    }
}
