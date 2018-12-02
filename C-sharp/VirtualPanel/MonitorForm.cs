using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VirtualPanel
{
    public partial class MonitorForm : Form
    {
        private ArduinoPort arduinoport;
        private bool monitor = true;
        private int lines = 0;

        public MonitorForm(ArduinoPort port)
        {
            arduinoport = port;
            InitializeComponent();
            arduinoport.MessageReceived += Arduinoport_MessageReceived;
        }

        private void Arduinoport_MessageReceived(object sender, MessageEventArgs<object> mse)
        {
                if ((ChannelId)mse.ChannelID == ChannelId.MonitorField_1) label1.Text = mse.Data.ToString();
                if ((ChannelId)mse.ChannelID == ChannelId.MonitorField_2) label2.Text = mse.Data.ToString();
                if ((ChannelId)mse.ChannelID == ChannelId.MonitorField_3) label3.Text = mse.Data.ToString();
                if ((ChannelId)mse.ChannelID == ChannelId.MonitorField_4) label4.Text = mse.Data.ToString();
                if ((ChannelId)mse.ChannelID == ChannelId.MonitorField_5) label5.Text = mse.Data.ToString();
                if ((ChannelId)mse.ChannelID == ChannelId.MonitorField_6) label6.Text = mse.Data.ToString();
                if ((ChannelId)mse.ChannelID == ChannelId.MonitorScrollBox)
                {
                    if (monitor) WriteMonitor(mse.Data.ToString());
                }
        }

        public void WriteMonitor(String inputline)
        {
            if (lines >= 1000)
            {
                textBox1.Text = "";
                lines = 0;
            }

            textBox1.AppendText(inputline + "\n");
            lines++;
        }

        public void MonitorClear()
        {
            textBox1.Text = "";
            lines = 0;
            label1.Text = "";
            label2.Text = "";
            label3.Text = "";
            label4.Text = "";
            label5.Text = "";
            label6.Text = "";
        }


        private void StatisticsForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Visible = false;
            e.Cancel = true;
        }

        private void ArduinoResetButton_Click(object sender, EventArgs e)
        {
            arduinoport.Reset();
        }

        private void MonitorHoldButton_Click(object sender, EventArgs e)
        {
            monitor = !monitor;
            if (monitor)
                MonitorHoldButton.Text = "hold";
            else
                MonitorHoldButton.Text = "resume";
        }

        private void ClearButton_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            lines = 0;
        }

        private void MonFileDialogButton_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                File.WriteAllText(saveFileDialog1.FileName, textBox1.Text);
            }
        }
    }
}
