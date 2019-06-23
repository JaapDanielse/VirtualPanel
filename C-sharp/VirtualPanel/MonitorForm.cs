using System;
using System.IO;
using System.Windows.Forms;
using System.Collections.Generic;

using ArduinoCom;
using System.Drawing;
using System.Text;

namespace VirtualPanel
{
    public partial class MonitorForm : Form
    {
        private ArduinoPort arduinoport;
        private bool monitor = true;
        private int lines = 0;
        private List<Tuple<ChannelId, Control>> pannelControlList;
        private List<String> log = new List<string>();

        private vp_type MonitorInputType_1 = vp_type.vp_int;
        private vp_type MonitorInputType_2 = vp_type.vp_int;
        private vp_type MonitorInputType_3 = vp_type.vp_int;
        private vp_type MonitorInputType_4 = vp_type.vp_int;
        private vp_type MonitorInputType_5 = vp_type.vp_int;
        private vp_type MonitorInputType_6 = vp_type.vp_int;

        private bool MonInput_1 = false;
        private bool MonInput_2 = false;
        private bool MonInput_3 = false;
        private bool MonInput_4 = false;
        private bool MonInput_5 = false;
        private bool MonInput_6 = false;

        private long MinMonInput_1 = long.MinValue;
        private long MinMonInput_2 = long.MinValue;
        private long MinMonInput_3 = long.MinValue;
        private long MinMonInput_4 = long.MinValue;
        private long MinMonInput_5 = long.MinValue;
        private long MinMonInput_6 = long.MinValue;

        private long MaxMonInput_1 = long.MaxValue;
        private long MaxMonInput_2 = long.MaxValue;
        private long MaxMonInput_3 = long.MaxValue;
        private long MaxMonInput_4 = long.MaxValue;
        private long MaxMonInput_5 = long.MaxValue;
        private long MaxMonInput_6 = long.MaxValue;

        private float MinMonInputF_1 = float.MinValue;
        private float MinMonInputF_2 = float.MinValue;
        private float MinMonInputF_3 = float.MinValue;
        private float MinMonInputF_4 = float.MinValue;
        private float MinMonInputF_5 = float.MinValue;
        private float MinMonInputF_6 = float.MinValue;

        private float MaxMonInputF_1 = float.MaxValue;
        private float MaxMonInputF_2 = float.MaxValue;
        private float MaxMonInputF_3 = float.MaxValue;
        private float MaxMonInputF_4 = float.MaxValue;
        private float MaxMonInputF_5 = float.MaxValue;
        private float MaxMonInputF_6 = float.MaxValue;


        public MonitorForm(ArduinoPort port)
        {
            arduinoport = port;
            InitializeComponent();
            arduinoport.MessageReceived += Arduinoport_MessageReceived;

            pannelControlList = new List<Tuple<ChannelId, Control>>();
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.MonitorField_1, label1));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.MonitorField_2, label2));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.MonitorField_3, label3));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.MonitorField_4, label4));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.MonitorField_5, label5));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.MonitorField_6, label6));

        }

        private void Arduinoport_MessageReceived(object sender, MessageEventArgs<object> mse)
        {

            if ((ChannelId)mse.ChannelID == ChannelId.MonitorField_1) label1.Text = mse.Data.ToString();
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorField_2) label2.Text = mse.Data.ToString();
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorField_3) label3.Text = mse.Data.ToString();
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorField_4) label4.Text = mse.Data.ToString();
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorField_5) label5.Text = mse.Data.ToString();
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorField_6) label6.Text = mse.Data.ToString();
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorLogPanel) WriteMonitor(mse.Data.ToString());

            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInput_1 && mse.Type == vp_type.vp_boolean) MonInput_1 = (bool)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInput_2 && mse.Type == vp_type.vp_boolean) MonInput_2 = (bool)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInput_3 && mse.Type == vp_type.vp_boolean) MonInput_3 = (bool)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInput_4 && mse.Type == vp_type.vp_boolean) MonInput_4 = (bool)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInput_5 && mse.Type == vp_type.vp_boolean) MonInput_5 = (bool)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInput_6 && mse.Type == vp_type.vp_boolean) MonInput_6 = (bool)mse.Data;

            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInputLabel_1 && mse.Type == vp_type.vp_string) MonitorInputLabel_1.Text = mse.Data.ToString();
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInputLabel_2 && mse.Type == vp_type.vp_string) MonitorInputLabel_2.Text = mse.Data.ToString();
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInputLabel_3 && mse.Type == vp_type.vp_string) MonitorInputLabel_3.Text = mse.Data.ToString();
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInputLabel_4 && mse.Type == vp_type.vp_string) MonitorInputLabel_4.Text = mse.Data.ToString();
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInputLabel_5 && mse.Type == vp_type.vp_string) MonitorInputLabel_5.Text = mse.Data.ToString();
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInputLabel_6 && mse.Type == vp_type.vp_string) MonitorInputLabel_6.Text = mse.Data.ToString();

            if ((ChannelId)mse.ChannelID == ChannelId.MinMonitorInput_1 && mse.Type == vp_type.vp_int) MinMonInput_1 = (int)mse.Data; 
            if ((ChannelId)mse.ChannelID == ChannelId.MinMonitorInput_2 && mse.Type == vp_type.vp_int) MinMonInput_2 = (int)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MinMonitorInput_3 && mse.Type == vp_type.vp_int) MinMonInput_3 = (int)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MinMonitorInput_4 && mse.Type == vp_type.vp_int) MinMonInput_4 = (int)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MinMonitorInput_5 && mse.Type == vp_type.vp_int) MinMonInput_5 = (int)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MinMonitorInput_6 && mse.Type == vp_type.vp_int) MinMonInput_6 = (int)mse.Data;

            if ((ChannelId)mse.ChannelID == ChannelId.MaxMonitorInput_1 && mse.Type == vp_type.vp_int) MaxMonInput_1 = (int)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MaxMonitorInput_2 && mse.Type == vp_type.vp_int) MaxMonInput_2 = (int)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MaxMonitorInput_3 && mse.Type == vp_type.vp_int) MaxMonInput_3 = (int)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MaxMonitorInput_4 && mse.Type == vp_type.vp_int) MaxMonInput_4 = (int)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MaxMonitorInput_5 && mse.Type == vp_type.vp_int) MaxMonInput_5 = (int)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MaxMonitorInput_6 && mse.Type == vp_type.vp_int) MaxMonInput_6 = (int)mse.Data;

            if ((ChannelId)mse.ChannelID == ChannelId.MinMonitorInput_1 && mse.Type == vp_type.vp_float) MinMonInputF_1 = (float)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MinMonitorInput_2 && mse.Type == vp_type.vp_float) MinMonInputF_2 = (float)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MinMonitorInput_3 && mse.Type == vp_type.vp_float) MinMonInputF_3 = (float)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MinMonitorInput_4 && mse.Type == vp_type.vp_float) MinMonInputF_4 = (float)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MinMonitorInput_5 && mse.Type == vp_type.vp_float) MinMonInputF_5 = (float)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MinMonitorInput_6 && mse.Type == vp_type.vp_float) MinMonInputF_6 = (float)mse.Data;

            if ((ChannelId)mse.ChannelID == ChannelId.MaxMonitorInput_1 && mse.Type == vp_type.vp_float) MaxMonInputF_1 = (float)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MaxMonitorInput_2 && mse.Type == vp_type.vp_float) MaxMonInputF_2 = (float)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MaxMonitorInput_3 && mse.Type == vp_type.vp_float) MaxMonInputF_3 = (float)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MaxMonitorInput_4 && mse.Type == vp_type.vp_float) MaxMonInputF_4 = (float)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MaxMonitorInput_5 && mse.Type == vp_type.vp_float) MaxMonInputF_5 = (float)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.MaxMonitorInput_6 && mse.Type == vp_type.vp_float) MaxMonInputF_6 = (float)mse.Data;


            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInput_1)
            {
                MonitorInputType_1 = mse.Type;
                if (MonitorInputType_1 != vp_type.vp_void && MonitorInputType_1 != vp_type.vp_boolean)
                {
                    MonitorInputPanel_1.Visible = true;
                    MonitorInputTextBox_1.Text = mse.Data.ToString();
                }
            }
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInput_2)
            {
                MonitorInputType_2 = mse.Type;
                if (MonitorInputType_2 != vp_type.vp_void && MonitorInputType_2 != vp_type.vp_boolean)
                {
                    MonitorInputPanel_2.Visible = true;
                    MonitorInputTextBox_2.Text = mse.Data.ToString();
                }
            }
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInput_3)
            {
                MonitorInputType_3 = mse.Type;
                if (MonitorInputType_3 != vp_type.vp_void && MonitorInputType_3 != vp_type.vp_boolean)
                {
                    MonitorInputTextBox_3.Text = mse.Data.ToString();
                    MonitorInputPanel_3.Visible = true;
                }
            }
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInput_4)
            {
                MonitorInputType_4 = mse.Type;
                if (MonitorInputType_4 != vp_type.vp_void && MonitorInputType_4 != vp_type.vp_boolean)
                {
                    MonitorInputPanel_4.Visible = true;
                    MonitorInputTextBox_4.Text = mse.Data.ToString();
                }
            }
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInput_5)
            {
                MonitorInputType_5 = mse.Type;
                if (MonitorInputType_5 != vp_type.vp_void && MonitorInputType_5 != vp_type.vp_boolean)
                {
                    MonitorInputPanel_5.Visible = true;
                    MonitorInputTextBox_5.Text = mse.Data.ToString();
                }
            }
            if ((ChannelId)mse.ChannelID == ChannelId.MonitorInput_6)
            {
                MonitorInputType_6 = mse.Type;
                if (MonitorInputType_6 != vp_type.vp_void && MonitorInputType_6 != vp_type.vp_boolean)
                {
                    MonitorInputPanel_6.Visible = true;
                    MonitorInputTextBox_6.Text = mse.Data.ToString();
                }
            }
        }

        public void WriteMonitor(String inputline)
        {
            log.Add(inputline + "\n");
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

            MonitorInputPanel_1.Visible = false;
            MonitorInputPanel_2.Visible = false;
            MonitorInputPanel_3.Visible = false;
            MonitorInputPanel_4.Visible = false;
            MonitorInputPanel_5.Visible = false;
            MonitorInputPanel_6.Visible = false;

            MonInput_1 = false;
            MonInput_2 = false;
            MonInput_3 = false;
            MonInput_4 = false;
            MonInput_5 = false;
            MonInput_6 = false;

            MonitorInputPanel_1.Visible = false;
            MonitorInputPanel_2.Visible = false;
            MonitorInputPanel_3.Visible = false;
            MonitorInputPanel_4.Visible = false;
            MonitorInputPanel_5.Visible = false;
            MonitorInputPanel_6.Visible = false;

            MinMonInput_1 = long.MinValue;
            MinMonInput_2 = long.MinValue;
            MinMonInput_3 = long.MinValue;
            MinMonInput_4 = long.MinValue;
            MinMonInput_5 = long.MinValue;
            MinMonInput_6 = long.MinValue;

            MaxMonInput_1 = long.MaxValue;
            MaxMonInput_2 = long.MaxValue;
            MaxMonInput_3 = long.MaxValue;
            MaxMonInput_4 = long.MaxValue;
            MaxMonInput_5 = long.MaxValue;
            MaxMonInput_6 = long.MaxValue;

            MinMonInputF_1 = float.MinValue;
            MinMonInputF_2 = float.MinValue;
            MinMonInputF_3 = float.MinValue;
            MinMonInputF_4 = float.MinValue;
            MinMonInputF_5 = float.MinValue;
            MinMonInputF_6 = float.MinValue;

            MaxMonInputF_1 = float.MaxValue;
            MaxMonInputF_2 = float.MaxValue;
            MaxMonInputF_3 = float.MaxValue;
            MaxMonInputF_4 = float.MaxValue;
            MaxMonInputF_5 = float.MaxValue;
            MaxMonInputF_6 = float.MaxValue;

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

        private void LabelInputRequest(object sender, EventArgs e)
        {
            if (sender == label1) if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.MonitorField_1);
            if (sender == label2) if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.MonitorField_2);
            if (sender == label3) if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.MonitorField_3);
            if (sender == label4) if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.MonitorField_4);
            if (sender == label5) if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.MonitorField_5);
            if (sender == label6) if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.MonitorField_6);
        }

        private void MonitorDiscardInput_Click(object sender, EventArgs e)
        {
            if (sender == MonitorDiscardInput_1)
            {
                if (!MonInput_1) MonitorInputPanel_1.Visible = false;
                if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.MonitorInput_1);
            }
            if (sender == MonitorDiscardInput_2)
            {
                if (!MonInput_2) MonitorInputPanel_2.Visible = false;
                if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.MonitorInput_2);
            }
            if (sender == MonitorDiscardInput_3)
            {
                if (!MonInput_3) MonitorInputPanel_3.Visible = false;
                if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.MonitorInput_3);
            }
            if (sender == MonitorDiscardInput_4)
            {
                if (!MonInput_4) MonitorInputPanel_4.Visible = false;
                if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.MonitorInput_4);
            }
            if (sender == MonitorDiscardInput_5)
            {
                if (!MonInput_5) MonitorInputPanel_5.Visible = false;
                if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.MonitorInput_5);
            }
            if (sender == MonitorDiscardInput_6)
            {
                if (!MonInput_6) MonitorInputPanel_6.Visible = false;
                if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.MonitorInput_6);
            }
        }


        private void MonitorSendInput_Click(object sender, EventArgs e)
        {
            long MinInput = 0;
            long MaxInput = 0;
            float MinInputF = 0;
            float MaxInputF = 0;

            byte InputValueByte = 0;
            short InputValueShort = 0;
            ushort InputValueUShort = 0;
            int InputValueLong = 0;
            uint InputValueULong = 0;
            float InputValueFloat = 0;
            Panel Panel = new Panel();
            TextBox TextBox = new TextBox();
            ChannelId MonitorInput = ChannelId.MonitorInput_1;
            vp_type MonitorInputType = vp_type.vp_int;
            bool MonInput = false;

            if (sender == MonitorSendInput_1)
            {
                Panel = MonitorInputPanel_1;
                TextBox = MonitorInputTextBox_1;
                MonitorInput = ChannelId.MonitorInput_1;
                MonitorInputType = MonitorInputType_1;
                MonInput = MonInput_1;
                MinInput = MinMonInput_1;
                MaxInput = MaxMonInput_1;
                MinInputF = MinMonInputF_1;
                MaxInputF = MaxMonInputF_1;
            }
            if (sender == MonitorSendInput_2)
            {
                Panel = MonitorInputPanel_2;
                TextBox = MonitorInputTextBox_2;
                MonitorInput = ChannelId.MonitorInput_2;
                MonitorInputType = MonitorInputType_2;
                MonInput = MonInput_2;
                MinInput = MinMonInput_2;
                MaxInput = MaxMonInput_2;
                MinInputF = MinMonInputF_2;
                MaxInputF = MaxMonInputF_2;
            }
            if (sender == MonitorSendInput_3)
            {
                Panel = MonitorInputPanel_3;
                TextBox = MonitorInputTextBox_3;
                MonitorInput = ChannelId.MonitorInput_3;
                MonitorInputType = MonitorInputType_3;
                MonInput = MonInput_3;
                MinInput = MinMonInput_3;
                MaxInput = MaxMonInput_3;
                MinInputF = MinMonInputF_3;
                MaxInputF = MaxMonInputF_3;
            }
            if (sender == MonitorSendInput_4)
            {
                Panel = MonitorInputPanel_4;
                TextBox = MonitorInputTextBox_4;
                MonitorInput = ChannelId.MonitorInput_4;
                MonitorInputType = MonitorInputType_4;
                MonInput = MonInput_4;
                MinInput = MinMonInput_4;
                MaxInput = MaxMonInput_4;
                MinInputF = MinMonInputF_4;
                MaxInputF = MaxMonInputF_4;
            }
            if (sender == MonitorSendInput_5)
            {
                Panel = MonitorInputPanel_5;
                TextBox = MonitorInputTextBox_5;
                MonitorInput = ChannelId.MonitorInput_5;
                MonitorInputType = MonitorInputType_5;
                MonInput = MonInput_5;
                MinInput = MinMonInput_5;
                MaxInput = MaxMonInput_5;
                MinInputF = MinMonInputF_5;
                MaxInputF = MaxMonInputF_5;
            }
            if (sender == MonitorSendInput_6)
            {
                Panel = MonitorInputPanel_6;
                TextBox = MonitorInputTextBox_6;
                MonitorInput = ChannelId.MonitorInput_6;
                MonitorInputType = MonitorInputType_6;
                MonInput = MonInput_6;
                MinInput = MinMonInput_6;
                MaxInput = MaxMonInput_6;
                MinInputF = MinMonInputF_6;
                MaxInputF = MaxMonInputF_6;
            }

            if (!MonInput) Panel.Visible = false;

            if ( MonitorInputType == vp_type.vp_byte && byte.TryParse(TextBox.Text, out InputValueByte)
                 && (InputValueByte >= MinInput && InputValueByte <= MaxInput))
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)MonitorInput, vp_type.vp_byte, InputValueByte);
            }
            else if ( MonitorInputType == vp_type.vp_int && Int16.TryParse(TextBox.Text, out InputValueShort) 
                      && (InputValueShort >= MinInput && InputValueShort <= MaxInput))
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)MonitorInput, vp_type.vp_int, InputValueShort);
            }
            else if ( MonitorInputType == vp_type.vp_uint && UInt16.TryParse(TextBox.Text, out InputValueUShort) 
                      && (InputValueUShort >= MinInput && InputValueUShort <= MaxInput))
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)MonitorInput, vp_type.vp_uint, InputValueUShort);
            }
            else if ( MonitorInputType == vp_type.vp_long && Int32.TryParse(TextBox.Text, out InputValueLong) 
                      && (InputValueLong >= MinInput && InputValueLong <= MaxInput))
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)MonitorInput, vp_type.vp_long, InputValueLong);
            }
            else if (MonitorInputType == vp_type.vp_ulong && UInt32.TryParse(TextBox.Text, out InputValueULong)
                      && (InputValueULong >= MinInput && InputValueULong <= MaxInput))
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)MonitorInput, vp_type.vp_ulong, InputValueULong);
            }
            else if (MonitorInputType == vp_type.vp_float && float.TryParse(TextBox.Text, out InputValueFloat)
                      && (InputValueFloat >= MinInputF && InputValueFloat <= MaxInputF))
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)MonitorInput, InputValueFloat);
            }
            else if (MonitorInputType == vp_type.vp_string && TextBox.Text.Length <= 35)
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)MonitorInput, TextBox.Text);
            }
            else
            {
                TextBox.ForeColor = Color.Red;
                Panel.Visible = true;
            }
        }

        private void MonitorInputTextBox_TextChange(object sender, EventArgs e)
        {

            long MinInput=0;
            long MaxInput=0;
            float MinInputF = 0;
            float MaxInputF = 0;

            byte InputValueByte = 0;
            short InputValueShort = 0;
            ushort InputValueUShort = 0;
            int InputValueLong = 0;
            uint InputValueULong = 0;
            float InputValueFloat = 0;

            bool ValueValid = false;

            TextBox TextBox = (TextBox)sender;
            vp_type MonitorInputType = vp_type.vp_int;

            if (sender == MonitorInputTextBox_1)
            { MonitorInputType = MonitorInputType_1; MinInput = MinMonInput_1; MaxInput = MaxMonInput_1; MinInputF = MinMonInputF_1; MaxInputF = MaxMonInputF_1; }
            if (sender == MonitorInputTextBox_2)
            { MonitorInputType = MonitorInputType_2; MinInput = MinMonInput_2; MaxInput = MaxMonInput_2; MinInputF = MinMonInputF_2; MaxInputF = MaxMonInputF_2; }
            if (sender == MonitorInputTextBox_3)
            { MonitorInputType = MonitorInputType_3; MinInput = MinMonInput_3; MaxInput = MaxMonInput_3; MinInputF = MinMonInputF_3; MaxInputF = MaxMonInputF_3; }
            if (sender == MonitorInputTextBox_4)
            { MonitorInputType = MonitorInputType_4; MinInput = MinMonInput_4; MaxInput = MaxMonInput_4; MinInputF = MinMonInputF_4; MaxInputF = MaxMonInputF_4; }
            if (sender == MonitorInputTextBox_5)
            { MonitorInputType = MonitorInputType_5; MinInput = MinMonInput_5; MaxInput = MaxMonInput_5; MinInputF = MinMonInputF_5; MaxInputF = MaxMonInputF_5; }
            if (sender == MonitorInputTextBox_6)
            { MonitorInputType = MonitorInputType_6; MinInput = MinMonInput_6; MaxInput = MaxMonInput_6; MinInputF = MinMonInputF_6; MaxInputF = MaxMonInputF_6; }


            TextBox.ForeColor = Color.Black;

            if (MonitorInputType == vp_type.vp_byte && byte.TryParse(TextBox.Text, out InputValueByte))
            {
                if (InputValueByte >= MinInput && InputValueByte <= MaxInput)
                {
                    TextBox.ForeColor = Color.Black;
                    ValueValid = true;
                }
            }
            else if (MonitorInputType == vp_type.vp_int && Int16.TryParse(TextBox.Text, out InputValueShort))
            {
                if (InputValueShort >= MinInput && InputValueShort <= MaxInput)
                {
                    TextBox.ForeColor = Color.Black;
                    ValueValid = true;
                }
            }
            else if (MonitorInputType == vp_type.vp_uint && UInt16.TryParse(TextBox.Text, out InputValueUShort))
            {
                if (InputValueUShort >= MinInput && InputValueUShort <= MaxInput)
                {
                    TextBox.ForeColor = Color.Black;
                    ValueValid = true;
                }
            }
            else if (MonitorInputType == vp_type.vp_long && Int32.TryParse(TextBox.Text, out InputValueLong))
            {
                if (InputValueLong >= MinInput && InputValueLong <= MaxInput)
                {
                    TextBox.ForeColor = Color.Black;
                    ValueValid = true;
                }
            }
            else if (MonitorInputType == vp_type.vp_ulong && UInt32.TryParse(TextBox.Text, out InputValueULong))
            {
                if (InputValueULong >= MinInput && InputValueULong <= MaxInput)
                {
                    TextBox.ForeColor = Color.Black;
                    ValueValid = true;
                }
            }
            else if (MonitorInputType == vp_type.vp_float && float.TryParse(TextBox.Text, out InputValueFloat))
            {
                if (InputValueFloat >= MinInputF && InputValueFloat <= MaxInputF)
                {
                    TextBox.ForeColor = Color.Black;
                    ValueValid = true;
                }
            }
            else if (MonitorInputType == vp_type.vp_string )
            {
                if (TextBox.Text.Length <= 35)
                {
                    TextBox.ForeColor = Color.Black;
                    ValueValid = true;
                }
            }

            if (!ValueValid) TextBox.ForeColor = Color.Red;
        }

        private void WriteLog_Tick(object sender, EventArgs e)
        {

            if (monitor)
            {
                StringBuilder builder = new StringBuilder();

                foreach (var line in log)
                {
                    builder.AppendLine(line);
                    lines++;

                    if (lines >= 2500)
                    {
                        builder.Clear();
                        textBox1.Clear();
                        lines = 0;
                    }
                }

                textBox1.AppendText(builder.ToString());
                log.Clear();
                builder.Clear();
            }

        }
    }
}
