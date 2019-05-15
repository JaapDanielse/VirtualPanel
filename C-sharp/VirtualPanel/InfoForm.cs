﻿using System;
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
                    InfoRichTextBox.Text = "";
                    InfoLabel.Text = "";
                }
            }

           if ((ChannelId)mse.ChannelID == ChannelId.InfoTitle && mse.Type == vp_type.vp_string)
            {
                InfoLabel.Text = ((string)mse.Data);
                InfoRichTextBox.Text="";
            }
            if ((ChannelId)mse.ChannelID == ChannelId.InfoText && mse.Type == vp_type.vp_string) InfoRichTextBox.AppendText(((string)mse.Data) + "\n");
        }

        private void InfoForm_Load(object sender, EventArgs e)
        {
            InfoRichTextBox.AppendText("Arduino Experiment controlpanel V1.0\n\n");
            InfoRichTextBox.AppendText("Functional design: Jaap Daniëlse\n");
            InfoRichTextBox.AppendText("Application design and development:\n");
            InfoRichTextBox.AppendText("Jaap, Tim, and Paul Daniëlse\n\n");
            InfoRichTextBox.AppendText("Copyright 2019, J.C. Daniëlse, Published under MIT Licence\n\n");
            InfoRichTextBox.AppendText("Documentation:\n https://github.com/JaapDanielse/VirtualPanel/wiki \n");

        }

        private void InfoForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Visible = false;
            e.Cancel = true;
        }

        // Event raised from RichTextBox when user clicks on a link:
        private void richTextBox_LinkClicked(object sender, LinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start(e.LinkText);
        }
     }
}
