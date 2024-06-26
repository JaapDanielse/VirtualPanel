﻿
// VirtualPanel Windows application - Documentation https://github.com/JaapDanielse/VirtualPanel/wiki/Basic-Examples
// MIT Licence - Copyright (c) 2020 Jaap Danielse - https://github.com/JaapDanielse/VirtualPanel
/*
 * V1.3.0 30-01-2021 JD - Key repeat
 * V1.2.1 25-01-2021 JD - Bugfix Input edit color reset on new input
 * 
 * 
 */



using System;
using System.Collections.Generic;
using System.Drawing;
using System.Media;
using System.Windows.Forms;

using ArduinoCom;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Threading;

namespace VirtualPanel
{
    public enum ChannelId
    {
        //
        ApplicationName, // ApplicationName
        PanelConnected,  // PanelConnected
        Reset,           // Reset
        DynamicDisplay,  // DynamicDisplay
        UnixTime,        // UnixTime
        Beep,            // Beep
        //
        Button_1,  // Button_1
        Button_2,  // Button_2
        Button_3,  // Button_3
        Button_4,  // Button_4
        Button_5,  // Button_5
        Button_6,  // Button_6
        Button_7,  // Button_7
        Button_8,  // Button_8
        Button_9,  // Button_9
        Button_10, // Button_10
        Button_11, // Button_11
        Button_12, // Button_12
        Button_13, // Button_13
        Button_14, // Button_14
        Button_15, // Button_15
        Button_16, // Button_16
        Button_17, // Button_17
        //
        Slider_1, // Slider_1
        Slider_2, // Slider_1
        Slider_3, // Slider_1
        Slider_4, // Slider_1
        Slider_5, // Slider_1
        //
        MaxSlider_1, // MaxSlider_1
        MaxSlider_2, // MaxSlider_1
        MaxSlider_3, // MaxSlider_1
        MaxSlider_4, // MaxSlider_1
        MaxSlider_5, // MaxSlider_1
        //
        Led_1,   // Led_1
        Led_2,   // Led_2
        Led_3,   // Led_3
        Led_4,   // Led_4
        Led_5,   // Led_5
        Led_6,   // Led_6
        Led_7,   // Led_7
        Led_8,   // Led_8
        Led_9,   // Led_9
        Led_10,  // Led_10
        Led_11,  // Led_11
        Led_12,  // Led_12
        Led_13,  // Led_13
        //
        Display_1, // Display 1
        Display_2, // Display 2
        Display_3, // Display 3
        Display_4, // Display 4
        //
        PanelInput_1, //
        PanelInput_2, //
        //
        MinPanelInput_1, //
        MinPanelInput_2, //
        //
        MaxPanelInput_1, //
        MaxPanelInput_2, //
        //
        PanelInputLabel_1, //
        PanelInputLabel_2, //
        // 
        Monitor,        // Monitor
        MonitorField_1, // MonitorField_1
        MonitorField_2, // MonitorField_2
        MonitorField_3, // MonitorField_3
        MonitorField_4, // MonitorField_4
        MonitorField_5, // MonitorField_5
        MonitorField_6, // MonitorField_6
        MonitorLog, // StatMonitor
        //
        MonitorInput_1, //
        MonitorInput_2, //
        MonitorInput_3, //
        MonitorInput_4, //
        MonitorInput_5, //
        MonitorInput_6, //
        //
        MinMonitorInput_1, //
        MinMonitorInput_2, //
        MinMonitorInput_3, //
        MinMonitorInput_4, //
        MinMonitorInput_5, //
        MinMonitorInput_6, //
        //
        MaxMonitorInput_1, //
        MaxMonitorInput_2, //
        MaxMonitorInput_3, //
        MaxMonitorInput_4, //
        MaxMonitorInput_5, //
        MaxMonitorInput_6, //
        //
        MonitorInputLabel_1, //
        MonitorInputLabel_2, //
        MonitorInputLabel_3, //
        MonitorInputLabel_4, //
        MonitorInputLabel_5, //
        MonitorInputLabel_6, //
        //
        Graph, // false/true, byte (1(draw), 2(stat), 3(run)
        GraphGrid, // byte number of segments
        GraphDrawLine, // ULong 4x byte (Fx,Fy,Tx,Ty) UInt 2 x byte (X,Y), color string, Pen size
        GraphDrawPixel, // UInt 2 x byte (X,Y), color string, pen size 
        GraphText, //
        //
        GraphValue_1, // byte 
        GraphValue_2, // byte 
        GraphValue_3, // byte 
        GraphValue_4, // byte 
        GraphValue_5, // byte
        //
        GraphValueCount_1, // int
        GraphValueCount_2, // int
        GraphValueCount_3, // int 
        GraphValueCount_4, // int  
        GraphValueCount_5, // int 
        //
        GraphCaption_1, //
        GraphCaption_2, //
        //
        GraphLabel_1, //
        GraphLabel_2, //
        GraphLabel_3, //
        GraphLabel_4, //
        GraphLabel_5, //
        //
        GraphButton_1, //
        GraphButton_2, //
        GraphButton_3, //
        GraphButton_4,  //
        //
        GraphClick, //
        GraphDoubleClick, //
        GraphRightClick, //
        //
        Info,
        InfoTitle,
        InfoText,
        //
        PanelColor, //
        //
        GraphDrawCircle, //
        //
        GraphInput_1, //
        GraphInput_2, //
        GraphInput_3, //
        GraphInput_4, //
        GraphInput_5, //
        //
        MinGraphInput_1, //
        MinGraphInput_2, //
        MinGraphInput_3, //
        MinGraphInput_4, //
        MinGraphInput_5, //
        //
        MaxGraphInput_1, //
        MaxGraphInput_2, //
        MaxGraphInput_3, //
        MaxGraphInput_4, //
        MaxGraphInput_5, //
        //
        GraphInputLabel_1, //
        GraphInputLabel_2, //
        GraphInputLabel_3, //
        GraphInputLabel_4, //
        GraphInputLabel_5, //
        //
        OpenFile_1, //
        OpenFile_2, //
        OpenFile_3, //
        OpenFile_4, //
        //
        ReadLineFile_1, //
        ReadLineFile_2, //
        ReadLineFile_3, //
        ReadLineFile_4, //
        //
        WriteLineFile_1, //
        WriteLineFile_2, //
        WriteLineFile_3, //
        WriteLineFile_4, //
        //
        ClearFile_1, //
        ClearFile_2, //
        ClearFile_3, //
        ClearFile_4, //
        //
        DeleteFile_1, //
        DeleteFile_2, //
        DeleteFile_3, //
        DeleteFile_4, //
        //
        FileOpenDialogTitle_1, //
        FileOpenDialogTitle_2, //
        FileOpenDialogTitle_3, //
        FileOpenDialogTitle_4, //
        //
        EndChannel //
    }

    public partial class VirtualPanelForm : Form
    {
        private MsgLogForm settings;
        private MonitorForm stats;
        private GraphForm graph;
        private InfoForm info;
        private ArduinoPort port;
        private bool searching = true;

        private List<Tuple<ChannelId, Control>> panelControlList;
        int MsgNum = 0;

        bool PanelConnected = false;

        private bool[] ButtonRepeat = new bool[17];

        private vp_type PanelInputType_1 = vp_type.vp_int;
        private vp_type PanelInputType_2 = vp_type.vp_int;

        private bool PanelInput_1 = false;
        private bool PanelInput_2 = false;

        private bool PanelInputColor_1 = false;
        private bool PanelInputColor_2 = false;

        private long MinPanelInput_1 = long.MinValue;
        private long MinPanelInput_2 = long.MinValue;

        private long MaxPanelInput_1 = long.MaxValue;
        private long MaxPanelInput_2 = long.MaxValue;

        private float MinPanelInputF_1 = float.MinValue;
        private float MinPanelInputF_2 = float.MinValue;
        private float MaxPanelInputF_1 = float.MaxValue;
        private float MaxPanelInputF_2 = float.MaxValue;

        private string PanelInputText_1 = "";
        private string PanelInputText_2 = "";

        public Color PanelColor = Color.DimGray;
        private Color PanelColorHoverColor = Color.LightGray;

        string dialogdir = "";

        FileHandle FileHandle_1 = new FileHandle();
        FileHandle FileHandle_2 = new FileHandle();
        FileHandle FileHandle_3 = new FileHandle();
        FileHandle FileHandle_4 = new FileHandle();

        String DialogTitleFile_1 = "VirtualPanel Open File 1";
        String DialogTitleFile_2 = "VirtualPanel Open File 2";
        String DialogTitleFile_3 = "VirtualPanel Open File 3";
        String DialogTitleFile_4 = "VirtualPanel Open File 4";

        public Point GraphLocation = new Point(0, 0);

        private Queue<Action> jobQueue = new Queue<Action>();
        private object queueLock = new object();


        public VirtualPanelForm(String preSelectedComPort, String preSelectedSpeedString)
        {
            InitializeComponent();

            panelControlList = new List<Tuple<ChannelId, Control>>();

            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_1, button1));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_2, button2));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_3, button3));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_4, button4));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_5, button5));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_6, button6));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_7, button7));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_8, button8));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_9, button9));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_10, button10));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_11, button11));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_12, button12));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_13, button13));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_14, button14));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_15, button15));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_16, button16));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_17, button17));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_1, Led1));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_2, Led2));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_3, Led3));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_4, Led4));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_5, Led5));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_6, Led6));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_7, Led7));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_8, Led8));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_9, Led9));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_10, Led10));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_11, Led11));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_12, Led12));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_13, Led13));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.ApplicationName, ApplicationTitle));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Display_1, display1));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Display_2, display2));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Display_3, display3));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Display_4, display4));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Slider_1, ScrollBar1));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Slider_2, ScrollBar2));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Slider_3, ScrollBar3));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Slider_4, ScrollBar4));
            panelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Slider_5, ScrollBar5));

            preSelectedComPort = preSelectedComPort.ToUpper();

            if (!preSelectedComPort.StartsWith("COM") || !preSelectedComPort.Substring(3).All(char.IsDigit))
            {
                Console.WriteLine("Pre Selected COM port" + preSelectedComPort + "is incorrectly formatted: shoud be COM(NUM)");
                preSelectedComPort = "";
            }

            Int32 ComSpeed;
            if(!Int32.TryParse(preSelectedSpeedString, out ComSpeed))
            {
                ComSpeed = 115200;
            }


            port = new ArduinoPort("[VirtualPanelV2]", preSelectedComPort, ComSpeed);

            menuStrip1.Renderer = new MenuRenderer();

            PreviousLocation = Location;

            stats = new MonitorForm(port);
            stats.Show();
            stats.Visible = false;

            settings = new MsgLogForm(port);
            settings.Show();
            settings.Visible = false;

            graph = new GraphForm(port);
            graph.Show();
            graph.Visible = false;

            info = new InfoForm(port);
            info.Show();
            info.Visible = false;

            Panel_Reset();
            panel1.Visible = false;

            port.Connected += Port_Connected;
            port.Disconnected += Port_Disconnected;
            port.MessageReceived += Port_MessageReceived;
            port.MessageError += Port_MessageError;
            port.SearchPortTimeout = TimeSpan.FromSeconds(2);
            port.SearchPollFrequency = TimeSpan.FromMilliseconds(200);
            
            // Start the worker thread
            Thread workerThread = new Thread(Worker);
            workerThread.IsBackground = true;
            workerThread.Start();

        }

        private void EnqueueJob(Action job)
        {
            lock (queueLock)
            {
                jobQueue.Enqueue(job);
                Monitor.Pulse(queueLock);
            }
        }

        private void Worker()
        {
            while (true)
            {
                Action job;
                lock (queueLock)
                {
                    while (jobQueue.Count == 0)
                    {
                        Monitor.Wait(queueLock);
                    }
                    job = jobQueue.Dequeue();
                }
                job(); // Execute the job
            }
        }

        private void VirtualPanelForm_Shown(object sender, EventArgs e)
        {
            port.Open();
            connected_box.BackColor = Color.DarkGreen;
        }

        private void VirtualPanelForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            port.Close();
            port.Connected -= Port_Connected;
            port.Disconnected -= Port_Disconnected;
            port.MessageReceived -= Port_MessageReceived;
            port.MessageError -= Port_MessageError;

            
        }

        private void Panel_Reset()
        {
            stats.Visible = false;
            settings.Visible = false;
            graph.Visible = false;
            info.Visible = false;

            foreach (var t in panelControlList)
            {
                t.Item2.ForeColor = Color.Black;
                t.Item2.Visible = false;
            }

            panel1.Visible = false;

            PanelColor = Color.DimGray;
            PanelColorHoverColor = Color.LightGray;

            menuStrip1.BackColor = PanelColor;
            ApplicationTitle.BackColor = PanelColor;
            toolStripMenuItem1.BackColor = PanelColor;
            connection_label.BackColor = PanelColor;
            pictureBox1.BackColor = PanelColor;
            pictureBox2.BackColor = PanelColor;
            graph.panel1.BackColor = PanelColor;
       
            settings.LogFormClear();
            stats.MonitorClear();
            graph.GraphPanelClear();
            //info.InfoPanelClear(); // we leave the panel intact on a reset. 

            scrolllabel1.Visible = false;
            scrolllabel2.Visible = false;
            scrolllabel3.Visible = false;
            scrolllabel4.Visible = false;
            scrolllabel5.Visible = false;
            SetScrollBarMax(ScrollBar1, 100);
            SetScrollBarMax(ScrollBar2, 100);
            SetScrollBarMax(ScrollBar3, 100);
            SetScrollBarMax(ScrollBar4, 100);
            ScrollBar5.Maximum = 100;
            ScrollBar1.Value = ScrollBar1.Maximum;
            ScrollBar2.Value = ScrollBar2.Maximum;
            ScrollBar3.Value = ScrollBar3.Maximum;
            ScrollBar4.Value = ScrollBar4.Maximum;
            ScrollBar5.Value = 0;

            ApplicationTitle.Text = "";
            ApplicationTitle.ForeColor = Color.White;
            ApplicationTitle.Font = new Font("Microsoft Sans Serif", 11);
            ApplicationTitle.Font = new Font(ApplicationTitle.Font, FontStyle.Bold);

            display1.Text = "";
            display1.ForeColor = Color.White;
            display1.Font = new Font("Microsoft Sans Serif", 14);
            display1.Font = new Font(display1.Font, FontStyle.Regular);
            display2.Text = "";
            display2.ForeColor = Color.White;
            display2.Font = new Font("Microsoft Sans Serif", 14);
            display2.Font = new Font(display2.Font, FontStyle.Regular);
            display3.Text = "";
            display3.ForeColor = Color.White;
            display3.Font = new Font("Microsoft Sans Serif", 14);
            display3.Font = new Font(display3.Font, FontStyle.Regular);
            display4.Text = "";
            display4.ForeColor = Color.White;
            display4.Font = new Font("Microsoft Sans Serif", 14);
            display4.Font = new Font(display4.Font, FontStyle.Regular);
            display3.BringToFront();
            display4.BringToFront();

            button1.Font = new Font("Microsoft Sans Serif", 8);
            button2.Font = new Font("Microsoft Sans Serif", 8);
            button3.Font = new Font("Microsoft Sans Serif", 8);
            button4.Font = new Font("Microsoft Sans Serif", 8);
            button5.Font = new Font("Microsoft Sans Serif", 8);
            button6.Font = new Font("Microsoft Sans Serif", 8);
            button7.Font = new Font("Microsoft Sans Serif", 8);
            button8.Font = new Font("Microsoft Sans Serif", 8);
            button9.Font = new Font("Microsoft Sans Serif", 8);
            button10.Font = new Font("Microsoft Sans Serif", 8);
            button11.Font = new Font("Microsoft Sans Serif", 8);
            button12.Font = new Font("Microsoft Sans Serif", 8);
            button13.Font = new Font("Microsoft Sans Serif", 8);
            button14.Font = new Font("Microsoft Sans Serif", 8);
            button15.Font = new Font("Microsoft Sans Serif", 8);
            button16.Font = new Font("Microsoft Sans Serif", 8);
            button17.Font = new Font("Microsoft Sans Serif", 8);
            button1.Font = new Font(button1.Font, FontStyle.Regular);
            button2.Font = new Font(button2.Font, FontStyle.Regular);
            button3.Font = new Font(button3.Font, FontStyle.Regular);
            button4.Font = new Font(button4.Font, FontStyle.Regular);
            button5.Font = new Font(button5.Font, FontStyle.Regular);
            button6.Font = new Font(button6.Font, FontStyle.Regular);
            button7.Font = new Font(button7.Font, FontStyle.Regular);
            button8.Font = new Font(button8.Font, FontStyle.Regular);
            button9.Font = new Font(button9.Font, FontStyle.Regular);
            button10.Font = new Font(button10.Font, FontStyle.Regular);
            button11.Font = new Font(button11.Font, FontStyle.Regular);
            button12.Font = new Font(button12.Font, FontStyle.Regular);
            button13.Font = new Font(button13.Font, FontStyle.Regular);
            button14.Font = new Font(button14.Font, FontStyle.Regular);
            button15.Font = new Font(button15.Font, FontStyle.Regular);
            button16.Font = new Font(button16.Font, FontStyle.Regular);
            button17.Font = new Font(button17.Font, FontStyle.Regular);

            for (int i=0; i<17; i++) // 17 = number of buttons
            {
               ButtonRepeat[i]=false;
            }

            timer1.Enabled = false;
            timer1.Interval = 500;
            panel1.Visible = true;

            PanelInputPanel_1.Visible = false;
            PanelInputPanel_2.Visible = false;

            PanelInputLabel_1.Text = "";
            PanelInputLabel_2.Text = "";

            PanelInput_1 = false;
            PanelInput_2 = false;

            PanelInputColor_1 = false;
            PanelInputColor_2 = false;

            MinPanelInput_1 = long.MinValue;
            MinPanelInput_2 = long.MinValue;
            MaxPanelInput_1 = long.MaxValue;
            MaxPanelInput_2 = long.MaxValue;

            MinPanelInputF_1 = float.MinValue;
            MinPanelInputF_2 = float.MinValue;
            MaxPanelInputF_1 = float.MaxValue;
            MaxPanelInputF_2 = float.MaxValue;

            dialogdir = "";

            FileHandle_1 = new FileHandle();
            FileHandle_2 = new FileHandle();
            FileHandle_3 = new FileHandle();
            FileHandle_4 = new FileHandle();

            DialogTitleFile_1 = "VirtualPanel Open File 1";
            DialogTitleFile_2 = "VirtualPanel Open File 2";
            DialogTitleFile_3 = "VirtualPanel Open File 3";
            DialogTitleFile_4 = "VirtualPanel Open File 4";

            if (port.IsConnected) port.Send((byte)ChannelId.PanelConnected);
            PanelConnected = true;
        }

        private void Port_Disconnected(object sender, ConnectedEventArgs e)
        {
            PanelConnected = false;
            connection_label.Text = "not connected";
            if (connected_box.BackColor == Color.Lime) connected_box.BackColor = Color.DarkGreen;

        }

        private void Port_Connected(object sender, ConnectedEventArgs args)
        {
            connection_label.Text = args.Portname;
            connected_box.BackColor = Color.Lime;
            Panel_Reset();
        }

        private void Port_MessageReceived(object sender, MessageEventArgs<object> mse)
        {
            MsgNum++;
            ChannelId id = (ChannelId) mse.ChannelID;

            Tuple<ChannelId, Control> control = panelControlList.Find(t => t.Item1 == id);

            if (control != null)
                SetAppearance(control.Item2, mse);
            else
            {
                if (id == ChannelId.UnixTime) SendUnixTime(mse);
                if (id == ChannelId.DynamicDisplay && mse.Type == vp_type.vp_boolean) timer1.Enabled = (bool)mse.Data;

                if (id == ChannelId.DynamicDisplay && mse.Type == vp_type.vp_int)
                {
                    if ((int)mse.Data >= 100 && (int)mse.Data <= 2500) timer1.Interval = (int)mse.Data;
                    timer1.Enabled = true;
                }
                if ((ChannelId)mse.ChannelID == ChannelId.PanelConnected && PanelConnected) port.Send((byte)ChannelId.PanelConnected);


                if ((ChannelId)mse.ChannelID == ChannelId.OpenFile_1 && (mse.Type == vp_type.vp_string || mse.Type == vp_type.vp_void)) FileOpen(FileHandle_1, ChannelId.OpenFile_1, (string)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.OpenFile_2 && (mse.Type == vp_type.vp_string || mse.Type == vp_type.vp_void)) FileOpen(FileHandle_2, ChannelId.OpenFile_2, (string)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.OpenFile_3 && (mse.Type == vp_type.vp_string || mse.Type == vp_type.vp_void)) FileOpen(FileHandle_3, ChannelId.OpenFile_3, (string)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.OpenFile_4 && (mse.Type == vp_type.vp_string || mse.Type == vp_type.vp_void)) FileOpen(FileHandle_4, ChannelId.OpenFile_4, (string)mse.Data);

                if ((ChannelId)mse.ChannelID == ChannelId.ReadLineFile_1 && mse.Type == vp_type.vp_void) FileReadLine(FileHandle_1, ChannelId.ReadLineFile_1);
                if ((ChannelId)mse.ChannelID == ChannelId.ReadLineFile_2 && mse.Type == vp_type.vp_void) FileReadLine(FileHandle_2, ChannelId.ReadLineFile_2);
                if ((ChannelId)mse.ChannelID == ChannelId.ReadLineFile_3 && mse.Type == vp_type.vp_void) FileReadLine(FileHandle_3, ChannelId.ReadLineFile_3);
                if ((ChannelId)mse.ChannelID == ChannelId.ReadLineFile_4 && mse.Type == vp_type.vp_void) FileReadLine(FileHandle_4, ChannelId.ReadLineFile_4);

                if ((ChannelId)mse.ChannelID == ChannelId.ReadLineFile_1 && mse.Type == vp_type.vp_long) FileHandle_1.MoveReadCaret((long)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.ReadLineFile_2 && mse.Type == vp_type.vp_long) FileHandle_2.MoveReadCaret((long)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.ReadLineFile_3 && mse.Type == vp_type.vp_long) FileHandle_3.MoveReadCaret((long)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.ReadLineFile_4 && mse.Type == vp_type.vp_long) FileHandle_4.MoveReadCaret((long)mse.Data);

                if ((ChannelId)mse.ChannelID == ChannelId.WriteLineFile_1 && mse.Type == vp_type.vp_string) FileWriteLine(FileHandle_1, ChannelId.WriteLineFile_1, (string)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.WriteLineFile_2 && mse.Type == vp_type.vp_string) FileWriteLine(FileHandle_2, ChannelId.WriteLineFile_2, (string)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.WriteLineFile_3 && mse.Type == vp_type.vp_string) FileWriteLine(FileHandle_3, ChannelId.WriteLineFile_3, (string)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.WriteLineFile_4 && mse.Type == vp_type.vp_string) FileWriteLine(FileHandle_4, ChannelId.WriteLineFile_4, (string)mse.Data);

                if ((ChannelId)mse.ChannelID == ChannelId.WriteLineFile_1 && mse.Type == vp_type.vp_long) FileHandle_1.MoveWriteCaret((long)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.WriteLineFile_2 && mse.Type == vp_type.vp_long) FileHandle_2.MoveWriteCaret((long)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.WriteLineFile_3 && mse.Type == vp_type.vp_long) FileHandle_3.MoveWriteCaret((long)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.WriteLineFile_4 && mse.Type == vp_type.vp_long) FileHandle_4.MoveWriteCaret((long)mse.Data);

                if ((ChannelId)mse.ChannelID == ChannelId.ClearFile_1 && mse.Type == vp_type.vp_void) FileHandle_1.Clear();
                if ((ChannelId)mse.ChannelID == ChannelId.ClearFile_2 && mse.Type == vp_type.vp_void) FileHandle_2.Clear();
                if ((ChannelId)mse.ChannelID == ChannelId.ClearFile_3 && mse.Type == vp_type.vp_void) FileHandle_3.Clear();
                if ((ChannelId)mse.ChannelID == ChannelId.ClearFile_4 && mse.Type == vp_type.vp_void) FileHandle_4.Clear();

                if ((ChannelId)mse.ChannelID == ChannelId.DeleteFile_1 && mse.Type == vp_type.vp_void) FileHandle_1.Delete();
                if ((ChannelId)mse.ChannelID == ChannelId.DeleteFile_2 && mse.Type == vp_type.vp_void) FileHandle_2.Delete();
                if ((ChannelId)mse.ChannelID == ChannelId.DeleteFile_3 && mse.Type == vp_type.vp_void) FileHandle_3.Delete();
                if ((ChannelId)mse.ChannelID == ChannelId.DeleteFile_4 && mse.Type == vp_type.vp_void) FileHandle_4.Delete();

                if ((ChannelId)mse.ChannelID == ChannelId.FileOpenDialogTitle_1 && mse.Type == vp_type.vp_string) DialogTitleFile_1 = (string)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.FileOpenDialogTitle_2 && mse.Type == vp_type.vp_string) DialogTitleFile_2 = (string)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.FileOpenDialogTitle_3 && mse.Type == vp_type.vp_string) DialogTitleFile_3 = (string)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.FileOpenDialogTitle_4 && mse.Type == vp_type.vp_string) DialogTitleFile_4 = (string)mse.Data;

                if (id == ChannelId.Beep && mse.Type == vp_type.vp_void) EnqueueJob(() => System.Console.Beep(500, 400));
                if (id == ChannelId.Beep && mse.Type == vp_type.vp_int) EnqueueJob(() => System.Console.Beep((int)mse.Data, 400));
                if (id == ChannelId.Beep && mse.Type == vp_type.vp_ulong)
                {
                    Int64 Data = (Int64)mse.Data;

                    int Frequency = (int)(Data >> 16);
                    int Duration = (int)(Data & 0x0000FFFF);
                    if (Frequency >= 37 && Frequency <= 32767)
                        EnqueueJob(() => System.Console.Beep(Frequency, Duration));
                }

                if (id == ChannelId.Monitor && mse.Type == vp_type.vp_boolean)
                {
                    stats.Location = new Point(Location.X, Location.Y + Height);
                    stats.Visible = (bool)mse.Data;
                }

                if (id == ChannelId.Graph && mse.Type == vp_type.vp_boolean)
                {
                    graph.Location = new Point(Location.X, Location.Y + Height);
                    graph.Visible = (bool)mse.Data;
                }

                if (id == ChannelId.Info && mse.Type == vp_type.vp_boolean)
                {
                    info.Location = new Point(Location.X + Width, Location.Y);
                    info.Visible = (bool)mse.Data;
                }

                if (id == ChannelId.Reset) Panel_Reset();
                if (id == ChannelId.MaxSlider_1 && mse.Type == vp_type.vp_int) SetScrollBarMax(ScrollBar1, (int)mse.Data);
                if (id == ChannelId.MaxSlider_2 && mse.Type == vp_type.vp_int) SetScrollBarMax(ScrollBar2, (int)mse.Data);
                if (id == ChannelId.MaxSlider_3 && mse.Type == vp_type.vp_int) SetScrollBarMax(ScrollBar3, (int)mse.Data);
                if (id == ChannelId.MaxSlider_4 && mse.Type == vp_type.vp_int) SetScrollBarMax(ScrollBar4, (int)mse.Data);
                if (id == ChannelId.MaxSlider_5 && mse.Type == vp_type.vp_int) ScrollBar5.Maximum = (int)mse.Data + ScrollBar5.LargeChange - 1;

                if ((ChannelId)mse.ChannelID == ChannelId.PanelInput_1 && mse.Type == vp_type.vp_boolean) PanelInput_1 = (bool)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.PanelInput_2 && mse.Type == vp_type.vp_boolean) PanelInput_2 = (bool)mse.Data;

                if ((ChannelId)mse.ChannelID == ChannelId.PanelInputLabel_1 && mse.Type == vp_type.vp_string) PanelInputLabel_1.Text = mse.Data.ToString();
                if ((ChannelId)mse.ChannelID == ChannelId.PanelInputLabel_2 && mse.Type == vp_type.vp_string) PanelInputLabel_2.Text = mse.Data.ToString();

                if ((ChannelId)mse.ChannelID == ChannelId.MinPanelInput_1 && mse.Type == vp_type.vp_int) MinPanelInput_1 = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinPanelInput_2 && mse.Type == vp_type.vp_int) MinPanelInput_2 = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinPanelInput_1 && mse.Type == vp_type.vp_long) MinPanelInput_1 = (long)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinPanelInput_2 && mse.Type == vp_type.vp_long) MinPanelInput_2 = (long)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinPanelInput_1 && mse.Type == vp_type.vp_float) MinPanelInputF_1 = (float)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinPanelInput_2 && mse.Type == vp_type.vp_float) MinPanelInputF_2 = (float)mse.Data;

                if ((ChannelId)mse.ChannelID == ChannelId.MaxPanelInput_1 && mse.Type == vp_type.vp_int) MaxPanelInput_1 = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxPanelInput_2 && mse.Type == vp_type.vp_int) MaxPanelInput_2 = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxPanelInput_1 && mse.Type == vp_type.vp_long) MaxPanelInput_1 = (long)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxPanelInput_2 && mse.Type == vp_type.vp_long) MaxPanelInput_2 = (long)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxPanelInput_1 && mse.Type == vp_type.vp_ulong) MaxPanelInput_1 = (long)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxPanelInput_2 && mse.Type == vp_type.vp_ulong) MaxPanelInput_2 = (long)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxPanelInput_1 && mse.Type == vp_type.vp_float) MaxPanelInputF_1 = (float)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxPanelInput_2 && mse.Type == vp_type.vp_float) MaxPanelInputF_2 = (float)mse.Data;

                if ((ChannelId)mse.ChannelID == ChannelId.PanelInput_1)
                {
                    if (mse.Type != vp_type.vp_void && mse.Type != vp_type.vp_boolean)
                    {
                        PanelInputType_1 = mse.Type;
                        PanelInputPanel_1.Visible = true;
                        PanelInputPanel_1.BringToFront();
                        PanelInputText_1 = mse.Data.ToString();
                        PanelInputColor_1 = false;
                        PanelInputTextBox_1.Text = PanelInputText_1;
                    }
                    if (mse.Type == vp_type.vp_boolean && (bool)mse.Data == false)
                    {
                        PanelInputPanel_1.Visible = false;
                    }
                }
                if ((ChannelId)mse.ChannelID == ChannelId.PanelInput_2)
                {
                    if (mse.Type != vp_type.vp_void && mse.Type != vp_type.vp_boolean)
                    {
                        PanelInputType_2 = mse.Type;
                        PanelInputPanel_2.Visible = true;
                        PanelInputPanel_2.BringToFront();
                        PanelInputText_2 = mse.Data.ToString();
                        PanelInputColor_2 = false;
                        PanelInputTextBox_2.Text = PanelInputText_2;
                    }
                    if (mse.Type == vp_type.vp_boolean && (bool)mse.Data == false)
                    {
                        PanelInputPanel_2.Visible = false;
                    }
                }
            }

            if ((ChannelId)mse.ChannelID == ChannelId.PanelColor && mse.Type == vp_type.vp_string) SetPanelColor((string)mse.Data);


        }

        private void SetAppearance(Control control, MessageEventArgs<object> mse)
        {
            if (control is Button && !SetButtonRepeat((Button)control, mse)) SetButtonAppearance((Button)control, mse);
            if (control is PictureBox) SetLedAppearance((PictureBox)control, mse);
            if (control is Label) SetDisplayAppearance((Label)control, mse);
            if (control is VScrollBar) SetScrollBarAppearance((VScrollBar)control, mse);
            if (control == ScrollBar5)
            {
                if (mse.Type == vp_type.vp_boolean && (bool)mse.Data == false)
                {
                    ScrollBar5.Visible = false;

                    scrolllabel5.Visible = false;
                }
                else
                {
                    ScrollBar5.Visible = true;
                    if (mse.Type == vp_type.vp_string)
                    {
                        scrolllabel5.Visible = true;
                        scrolllabel5.Text = (string)mse.Data;
                        button5.Visible = false;
                        button6.Visible = false;
                        button7.Visible = false;
                    }
                    if (mse.Type == vp_type.vp_int)
                    {
                        if ((int)mse.Data <= (ScrollBar5.Maximum) && (int)mse.Data >= 0)
                            ScrollBar5.Value = (int)mse.Data;
                    }

                }

            }
        }

        private void FileWriteLine(FileHandle file, ChannelId replyChannel, string line)
        {
            if (!file.isOpen)
            {
                return;
            }

            file.WriteLine(line);
        }


        private void FileOpen(FileHandle file, ChannelId replyChannel, string filestring)
        {
            OpenFileDialog FileDialogUsed = new OpenFileDialog();

            if (file == FileHandle_1)
            {
                FileDialogUsed = openFileDialog1;
                FileDialogUsed.Title = DialogTitleFile_1;
            }

            if (file == FileHandle_2)
            {
                FileDialogUsed = openFileDialog2;
                FileDialogUsed.Title = DialogTitleFile_2;
            }

            if (file == FileHandle_3)
            {
                FileDialogUsed = openFileDialog3;
                FileDialogUsed.Title = DialogTitleFile_3;
            }

            if (file == FileHandle_4)
            {
                FileDialogUsed = openFileDialog4;
                FileDialogUsed.Title = DialogTitleFile_4;
            }

            FileDialogUsed.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
            FileDialogUsed.FilterIndex = 1;
            FileDialogUsed.FileName = "";

            string fdir = "";
            string fnam = "";
            string fext = "";
            bool wild = false;
            bool dirok = false;
            bool forcecreate = false;

            if (filestring.Contains("/F") || filestring.Contains("/f"))
            {
                var test = filestring.Split('/');
                filestring = test[0];
                forcecreate = true;
            }

            try { fdir = Path.GetDirectoryName(filestring); } catch (Exception ex) { };
            try { fnam = Path.GetFileName(filestring); } catch (Exception ex) { };
            try { fext = Path.GetExtension(filestring); } catch (Exception ex) { };

            if (fnam.Contains("*")) wild = true;

            if (fdir != "")
                dirok = false;
            else if (dialogdir != "")
                dirok = true;

            // check if directory exists
            if (fdir != "" && Directory.Exists(fdir + "\\"))
            {
                dialogdir = fdir + "\\";
                dirok = true;
                FileDialogUsed.InitialDirectory = dialogdir;
                if (fnam == "")
                { // no file specified, only a (existing) directory, set 
                    return;
                }
            } // dialogdir is set. If there was no file or wildcard we exit.

            if (fnam != "" && !wild)
            {
                FileDialogUsed.FileName = fnam;
                if (fext != "")
                    FileDialogUsed.Filter = fext.Remove(0, 1) + " files|*" + fext + "|All files (*.*)|*.*";
                else
                    FileDialogUsed.Filter = "All files (*.*)|*.*";
            }

            if (File.Exists(dialogdir + fnam) && !wild && forcecreate)
            { // open existing file
                int LineCount = file.Open(dialogdir + fnam);
                if (port.IsConnected) port.Send((byte)replyChannel, vp_type.vp_long, LineCount);
                return;
            }

            if (wild)
            { // set wildcard filter
                FileDialogUsed.Filter = fext.Remove(0, 1) + " files|*" + fext + "|All files (*.*)|*.*";
            }

            if (!wild && dirok && fnam != "" && fext != "" && forcecreate)
            { // force create a new file and open
                File.Create(dialogdir + fnam).Close();
                int LineCount = file.Open(dialogdir + fnam);
                if (port.IsConnected) port.Send((byte)replyChannel, vp_type.vp_long, LineCount);
                return;
            }

            // open dialog
            if (FileDialogUsed.ShowDialog() == DialogResult.OK)
            { // dialog ok, if not exist create and open
                if (!File.Exists(FileDialogUsed.FileName))
                    File.Create(FileDialogUsed.FileName).Close(); 
                dialogdir = Path.GetDirectoryName(FileDialogUsed.FileName) + "\\"; // save dialog dir.
                int LineCount = file.Open(FileDialogUsed.FileName);
                if (port.IsConnected) port.Send((byte)replyChannel, vp_type.vp_long, LineCount);
            }
            else
            {
                if (port.IsConnected) port.Send((byte)replyChannel);
            }
        }

       private void FileReadLine(FileHandle file, ChannelId replyChannel)
        {
            if (!file.isOpen)
            {
                return;
            }

            string line = file.ReadLine();

            if (line != null)
            {
                if (port.IsConnected) { port.Send((byte)replyChannel, line); }
            }
            else
            {
                if (port.IsConnected) { port.Send((byte)replyChannel); } // end of file: send void.
            }
        }

        public static Color String2Color(string ColorString)
        {
            Color convertedColor = Color.Empty;

            if (ColorString == "$YELLOW") convertedColor = Color.Yellow;
            if (ColorString == "$ORANGE") convertedColor = Color.Orange;
            if (ColorString == "$RED") convertedColor = Color.Red;
            if (ColorString == "$LBLUE") convertedColor = Color.DeepSkyBlue;
            if (ColorString == "$BLUE") convertedColor = Color.DodgerBlue;
            if (ColorString == "$DBLUE") convertedColor = Color.MidnightBlue;
            if (ColorString == "$PINK") convertedColor = Color.Fuchsia;
            if (ColorString == "$PURPLE") convertedColor = Color.SlateBlue;
            if (ColorString == "$DPURPLE") convertedColor = Color.DarkSlateBlue;
            if (ColorString == "$BROWN") convertedColor = Color.Sienna;
            if (ColorString == "$GREEN") convertedColor = Color.Lime;
            if (ColorString == "$GRAY") convertedColor = Color.DarkGray;
            if (ColorString == "$WHITE") convertedColor = Color.White;
            if (ColorString == "$BLACK") convertedColor = Color.Black;
            if (ColorString == "$OFF") convertedColor = Color.Black;
            if (ColorString == "$DEL") convertedColor = Color.Black;
            if (ColorString == "$DELETE") convertedColor = Color.Black;

            return convertedColor;
        }


        private void SetPanelColor(string ColorString)
        {
            if (ColorString == "$YELLOW") PanelColor = Color.Goldenrod;
            if (ColorString == "$ORANGE") PanelColor = Color.Tomato;
            if (ColorString == "$RED") PanelColor = Color.IndianRed;
            if (ColorString == "$BLUE") PanelColor = Color.CornflowerBlue;
            if (ColorString == "$PINK") PanelColor = Color.PaleVioletRed;
            if (ColorString == "$PURPLE") PanelColor = Color.MediumPurple;
            if (ColorString == "$BROWN") PanelColor = Color.Peru;
            if (ColorString == "$GREEN") PanelColor = Color.LightSeaGreen;
            if (ColorString == "$GRAY") PanelColor = Color.DimGray;
            if (ColorString == "$WHITE") PanelColor = Color.White;
            if (ColorString == "$BLACK") PanelColor = Color.Black;

            menuStrip1.BackColor = PanelColor;
            ApplicationTitle.BackColor = PanelColor;
            toolStripMenuItem1.BackColor = PanelColor;
            connection_label.BackColor = PanelColor;
            pictureBox1.BackColor = PanelColor;
            pictureBox2.BackColor = PanelColor;
            graph.panel1.BackColor = PanelColor;
        }

        public static void SetButtonAppearance(Button button, MessageEventArgs<object> mse)
        {
            int channelId = mse.ChannelID;

            if (mse.Type == vp_type.vp_boolean && (bool)mse.Data == false)
                button.Visible = false;
            else
                button.Visible = true;

            if (mse.Type == vp_type.vp_string)
            {
                Color col = String2Color((string)mse.Data);

                if (!col.IsEmpty)
                {
                    button.ForeColor = col; //
                }
                else if ((string)mse.Data == "$SMALL")
                {
                    button.Font = new Font("Microsoft Sans Serif", 7);
                    button.Font = new Font(button.Font, FontStyle.Regular);
                }
                else if ((string)mse.Data == "$NORMAL")
                {
                    button.Font = new Font("Microsoft Sans Serif", 8);
                    button.Font = new Font(button.Font, FontStyle.Regular);
                }
                else if ((string)mse.Data == "$BOLD")
                {
                    button.Font = new Font(button.Font, FontStyle.Bold);
                }
                else if ((string)mse.Data == "$BIG")
                {
                    button.Font = new Font("Microsoft Sans Serif", 11);
                }
                else if ((string)mse.Data == "$6PT")
                {
                    button.Font = new Font("Microsoft Sans Serif", 6);
                }
                else if ((string)mse.Data == "$7PT")
                {
                    button.Font = new Font("Microsoft Sans Serif", 7);
                }
                else if ((string)mse.Data == "$8PT")
                {
                    button.Font = new Font("Microsoft Sans Serif", 8);
                }
                else if ((string)mse.Data == "$9PT")
                {
                    button.Font = new Font("Microsoft Sans Serif", 8);
                }
                else if ((string)mse.Data == "$10PT")
                {
                    button.Font = new Font("Microsoft Sans Serif", 10);
                }
                else if ((string)mse.Data == "$11PT")
                {
                    button.Font = new Font("Microsoft Sans Serif", 11);
                }
                else if ((string)mse.Data == "$12PT")
                {
                    button.Font = new Font("Microsoft Sans Serif", 12);
                }
                else if ((string)mse.Data == "$14PT")
                {
                    button.Font = new Font("Microsoft Sans Serif", 14);
                }
                else if ((string)mse.Data == "$16PT")
                {
                    button.Font = new Font("Microsoft Sans Serif", 16);
                }
                else if ((string)mse.Data == "$18PT")
                {
                    button.Font = new Font("Microsoft Sans Serif", 18);
                }
                else
                {
                    button.Text = (string)mse.Data;
                }
            }
            else
            {
                button.Text = mse.Data.ToString();
            }
        }

        public bool SetButtonRepeat(Button button, MessageEventArgs<object> mse)
        {
            int channelId = mse.ChannelID - Convert.ToInt32(ChannelId.Button_1);

            if (mse.Type == vp_type.vp_string)
            {
                if ((string)mse.Data == "$REPEAT")
                {
                    ButtonRepeat[channelId] = true;
                    return true;
                }
                if ((string)mse.Data == "$NOREPEAT")
                {
                    ButtonRepeat[channelId] = false;
                    return true;
                }
            }
            return false;
        }

        private void SetLedAppearance(PictureBox led, MessageEventArgs<object> mse)
        {
            int channelId = mse.ChannelID;

            if (mse.Type == vp_type.vp_boolean) led.Visible = (bool)mse.Data;

            if (mse.Type == vp_type.vp_string)
            {
                Color col = String2Color((string)mse.Data);

                if (!col.IsEmpty)
                {
                    led.BackColor = col; //
                }
                led.Visible = true;
            }
        }


        private void SetDisplayAppearance(Label display, MessageEventArgs<object> mse)
        {
            display.Visible = true;

            if (mse.Type == vp_type.vp_boolean)
            {
                if (!(bool)mse.Data)
                    display.Visible = false;
            }
            else if (mse.Type == vp_type.vp_string)
            {
                Color col = String2Color((string)mse.Data);

                if (!col.IsEmpty)
                {
                    display.ForeColor = col; //
                }
                else if ((string)mse.Data == "$BOLD")
                {
                    display.Font = new Font(display.Font, FontStyle.Bold);
                }
                else if ((string)mse.Data == "$NORMAL")
                {
                    display.Font = new Font("Microsoft Sans Serif", 14);
                    display.Font = new Font(display.Font, FontStyle.Regular);
                }
                else if ((string)mse.Data == "$BIG")
                {
                    display.Font = new Font("Microsoft Sans Serif", 18);
                }
                else if ((string)mse.Data == "$SMALL")
                {
                    display.Font = new Font("Microsoft Sans Serif", 12);
                }
                else if ((string)mse.Data == "$10PT")
                {
                    display.Font = new Font("Microsoft Sans Serif", 10);
                }
                else if ((string)mse.Data == "$11PT")
                {
                    display.Font = new Font("Microsoft Sans Serif", 11);
                }
                else if ((string)mse.Data == "$12PT")
                {
                    display.Font = new Font("Microsoft Sans Serif", 12);
                }
                else if ((string)mse.Data == "$13PT")
                {
                    display.Font = new Font("Microsoft Sans Serif", 13);
                }
                else if ((string)mse.Data == "$14PT")
                {
                    display.Font = new Font("Microsoft Sans Serif", 14);
                }
                else if ((string)mse.Data == "$16PT")
                {
                    display.Font = new Font("Microsoft Sans Serif", 16);
                }
                else if ((string)mse.Data == "$18PT")
                {
                    display.Font = new Font("Microsoft Sans Serif", 18);
                }
                else
                {
                    display.Text = (string)mse.Data;
                }

            }
            else
            {
                display.Text = mse.Data.ToString();
            }

            if (display.Name == display3.Name && display.Visible == true && PanelInputPanel_1.Visible == false) display.BringToFront();
            if (display.Name == display4.Name && display.Visible == true && PanelInputPanel_2.Visible == false) display.BringToFront();
        }

        private void SetScrollBarMax(VScrollBar ScrollBar, int MaxValue)
        {
            if (MaxValue < 0)
                MaxValue = 100; 
            ScrollBar.LargeChange = 1;
            ScrollBar.Maximum = MaxValue;
            ScrollBar.Value = MaxValue;
        }

        private void SetScrollBarAppearance(VScrollBar scrollBar, MessageEventArgs<object> mse)
        {
            int channelId = mse.ChannelID;

            if (mse.Type == vp_type.vp_boolean && (bool)mse.Data == false)
            {
                scrollBar.Visible = false;
                if (scrollBar.Name == "ScrollBar1") scrolllabel1.Visible = false;
                if (scrollBar.Name == "ScrollBar2") scrolllabel2.Visible = false;
                if (scrollBar.Name == "ScrollBar3") scrolllabel3.Visible = false;
                if (scrollBar.Name == "ScrollBar4") scrolllabel4.Visible = false;
             }
            else
            {
                scrollBar.Visible = true;
                if (mse.Type == vp_type.vp_string)
                {
                    if (scrollBar.Name == "ScrollBar1")
                    {
                        scrolllabel1.Visible = true;
                        scrolllabel1.Text = (string)mse.Data;
                        button1.Visible = false;
                        button2.Visible = false;
                        button3.Visible = false;
                    }
                    if (scrollBar.Name == "ScrollBar2")
                    {
                        scrolllabel2.Visible = true;
                        scrolllabel2.Text = (string)mse.Data;
                        button9.Visible = false;
                        button10.Visible = false;
                        button11.Visible = false;
                    }
                    if (scrollBar.Name == "ScrollBar3")
                    {
                        scrolllabel3.Visible = true;
                        scrolllabel3.Text = (string)mse.Data;
                        button12.Visible = false;
                        button13.Visible = false;
                        button14.Visible = false;
                    }
                    if (scrollBar.Name == "ScrollBar4")
                    {
                        scrolllabel4.Visible = true;
                        scrolllabel4.Text = (string)mse.Data;
                        button15.Visible = false;
                        button16.Visible = false;
                        button17.Visible = false;
                    }
                }
                if (mse.Type == vp_type.vp_int)
                {
                    if (scrollBar.Name == "ScrollBar1")
                        if ((int)mse.Data <= ScrollBar1.Maximum && (int)mse.Data >= 0)
                            ScrollBar1.Value = ScrollBar1.Maximum - (int)mse.Data;
                    if (scrollBar.Name == "ScrollBar2")
                        if ((int)mse.Data <= ScrollBar2.Maximum && (int)mse.Data >= 0)
                            ScrollBar2.Value = ScrollBar2.Maximum - (int)mse.Data;
                    if (scrollBar.Name == "ScrollBar3")
                        if ((int)mse.Data <= ScrollBar3.Maximum && (int)mse.Data >= 0)
                            ScrollBar3.Value = ScrollBar3.Maximum - (int)mse.Data;
                    if (scrollBar.Name == "ScrollBar4")
                        if ((int)mse.Data <= ScrollBar4.Maximum && (int)mse.Data >= 0)
                            ScrollBar4.Value = ScrollBar4.Maximum - (int)mse.Data;
                }
            }
        }


        private void SendUnixTime(MessageEventArgs<object> mse)
        {
            int channelId = mse.ChannelID;
            int timestamp = (int)(DateTime.Now.Subtract(new DateTime(1970, 1, 1))).TotalSeconds;
            if (port.IsConnected) port.Send((byte)channelId, vp_type.vp_ulong, timestamp);
        }


        private void button_Click(object sender, EventArgs e)
        {
            Tuple<ChannelId, Control> channel = panelControlList.Find(t => t.Item2 == sender);
            if (channel != null)
            {
                int i = ButtonId - Convert.ToByte(ChannelId.Button_1);
                if (!ButtonRepeat[i])
                {
                    if (port.IsConnected) port.Send((byte)channel.Item1);
                }
            }
        }

        private byte ButtonId = 0;

        private void button_MouseDown(object sender, MouseEventArgs e)
        {
            Tuple<ChannelId, Control> channel = panelControlList.Find(t => t.Item2 == sender);
            if (channel != null)
            {
                ButtonId = (byte)channel.Item1;
                int i = ButtonId - Convert.ToByte(ChannelId.Button_1);
                if (ButtonRepeat[i])
                {
                    if (port.IsConnected) port.Send((byte)channel.Item1);
                    ButtonRepeatTimer.Interval = 500;
                    ButtonRepeatTimer.Enabled = true;
                }
            }
        }

        private void button_MouseUp(object sender, MouseEventArgs e)
        {
            ButtonRepeatTimer.Enabled = false;
        }

        private void ButtonRepeatTimer_Tick(object sender, EventArgs e)
        {
            if (port.IsConnected) port.Send(ButtonId);
            ButtonRepeatTimer.Interval = 150;
        }

        private void button_Repeate(object sender, EventArgs e)
        {
            Tuple<ChannelId, Control> channel = panelControlList.Find(t => t.Item2 == sender);
            if (channel != null)
            {
                if (port.IsConnected) port.Send((byte)channel.Item1);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {

            if (port.IsConnected) port.Send((byte)ChannelId.DynamicDisplay);
        }

        private void ScrollBar_Scroll(object sender, ScrollEventArgs e)
        {
           Tuple<ChannelId, Control> channel = panelControlList.Find(t => t.Item2 == sender);
           if (channel != null)
           {
              VScrollBar temp = (VScrollBar)channel.Item2;
              int Value = (temp.Maximum - temp.LargeChange + 1) - e.NewValue;
              if (port.IsConnected) port.Send((byte)channel.Item1, vp_type.vp_int, Value);
           }
        }


        private void monitorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (stats.Visible == true)
            {
                stats.Visible = false;
            }
            else
            {
                stats.Location = new Point(Location.X, Location.Y + Height);
                stats.Visible = true;
            }
        }

        private void messageLogToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (settings.Visible == true)
            {
                settings.Visible = false;
            }
            else
            {
                settings.Location = new Point(Location.X, Location.Y + Height);
                settings.Visible = true;
            }
        }


        private void connected_box_Click(object sender, EventArgs e)
        {
            if (!port.IsConnected)
            {
                if (searching)
                {
                    searching = false;
                    port.Close();
                    connected_box.BackColor = Color.Black;
                }
                else
                {
                    searching = true;
                    port.Open();
                    connected_box.BackColor = Color.DarkGreen;
                }
            }
            else
            {
                searching = false;
                port.Close();
                connected_box.BackColor = Color.Black;
            }
        }

        private void Port_MessageError(object sender, MessageEventArgs<object> mse)
        {
            if (port.IsConnected)
            {
                connected_box.BackColor = Color.Orange;
                ShowMsgErr.Enabled = true;
            }
        }

        private void graphToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (graph.Visible == true)
            {
                graph.Visible = false;
            }
            else
            {
                graph.Location = new Point(Location.X, Location.Y + Height);
                graph.Visible = true;
            }
        }


        private void mouseHover(object sender, EventArgs e)
        {
            pictureBox2.BackColor = PanelColorHoverColor;
        }


        private void mouseLeave(object sender, EventArgs e)
        {
            pictureBox2.BackColor = PanelColor;
        }


        private void resetArduinoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            port.Reset();
        }

        private void display_Click(object sender, EventArgs e)
        {
            if (sender == display1) if (port.IsConnected) port.Send((byte)ChannelId.Display_1);
            if (sender == display2) if (port.IsConnected) port.Send((byte)ChannelId.Display_2);
            if (sender == display3) if (port.IsConnected) port.Send((byte)ChannelId.Display_3);
            if (sender == display4) if (port.IsConnected) port.Send((byte)ChannelId.Display_4);

        }

        private void PanelInputTextBox_TextChange(object sender, EventArgs e)
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

            bool ValueValid = false;
            Color EditColor = Color.FromArgb(255, 64, 64, 64);

            // PanelSendInput_1
            // PanelSendInput_2
            // PanelDiscardInput_1

            

            if (sender == PanelInputTextBox_1 && !PanelInputColor_1) 
            { EditColor = Color.White; PanelInputColor_1 = true; }
            if (sender == PanelInputTextBox_2 && !PanelInputColor_2) 
            { EditColor = Color.White; PanelInputColor_2 = true; }

            TextBox TextBox = (TextBox)sender;
            vp_type InputType = vp_type.vp_int;

            if (sender == PanelInputTextBox_1)
            { 
                InputType = PanelInputType_1; MinInput = MinPanelInput_1; MaxInput = MaxPanelInput_1; MinInputF = MinPanelInputF_1; MaxInputF = MaxPanelInputF_1;
                AcceptButton = PanelSendInput_1; CancelButton = PanelDiscardInput_1;
            }

            if (sender == PanelInputTextBox_2)
            { 
                InputType = PanelInputType_2; MinInput = MinPanelInput_2; MaxInput = MaxPanelInput_2; MinInputF = MinPanelInputF_2; MaxInputF = MaxPanelInputF_2;
                AcceptButton = PanelSendInput_2; CancelButton = PanelDiscardInput_2;
            }


            if (InputType == vp_type.vp_byte && byte.TryParse(TextBox.Text, out InputValueByte))
            {
                if (InputValueByte >= MinInput && InputValueByte <= MaxInput)
                {
                    TextBox.ForeColor = EditColor;
                    ValueValid = true;
                }
            }
            else if (InputType == vp_type.vp_int && Int16.TryParse(TextBox.Text, out InputValueShort))
            {
                if (InputValueShort >= MinInput && InputValueShort <= MaxInput)
                {
                    TextBox.ForeColor = EditColor;
                    ValueValid = true;
                }
            }
            else if (InputType == vp_type.vp_uint && UInt16.TryParse(TextBox.Text, out InputValueUShort))
            {
                if (InputValueUShort >= MinInput && InputValueUShort <= MaxInput)
                {
                    TextBox.ForeColor = EditColor;
                    ValueValid = true;
                }
            }
            else if (InputType == vp_type.vp_long && Int32.TryParse(TextBox.Text, out InputValueLong))
            {
                if (InputValueLong >= MinInput && InputValueLong <= MaxInput)
                {
                    TextBox.ForeColor = EditColor;
                    ValueValid = true;
                }
            }
            else if (InputType == vp_type.vp_ulong && UInt32.TryParse(TextBox.Text, out InputValueULong))
            {
                if (InputValueULong >= MinInput && InputValueULong <= MaxInput)
                {
                    TextBox.ForeColor = EditColor;
                    ValueValid = true;
                }
            }
            else if (InputType == vp_type.vp_float && float.TryParse(TextBox.Text, out InputValueFloat))
            {
                if (InputValueFloat >= MinInputF && InputValueFloat <= MaxInputF)
                {
                    TextBox.ForeColor = EditColor;
                    ValueValid = true;
                }
            }
            else if (InputType == vp_type.vp_string)
            {
                if (TextBox.Text.Length <= 35 && (TextBox.Text.Length >= MinInput && TextBox.Text.Length <= MaxInput))
                {
                    TextBox.ForeColor = EditColor;
                    ValueValid = true;
                }
            }

            if (!ValueValid) TextBox.ForeColor = Color.Red;
        }

        private void PanelSendInput_Click(object sender, EventArgs e)
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
            ChannelId PanelInput = ChannelId.PanelInput_1;
            vp_type PanelInputType = vp_type.vp_int;
            bool MonInput = false;
            bool Valid = true;

            if (sender == PanelSendInput_1)
            {
                Panel = PanelInputPanel_1;
                TextBox = PanelInputTextBox_1;
                PanelInput = ChannelId.PanelInput_1;
                PanelInputType = PanelInputType_1;
                MonInput = PanelInput_1;
                MinInput = MinPanelInput_1;
                MaxInput = MaxPanelInput_1;
                MinInputF = MinPanelInputF_1;
                MaxInputF = MaxPanelInputF_1;
            }
            else if (sender == PanelSendInput_2)
            {
                Panel = PanelInputPanel_2;
                TextBox = PanelInputTextBox_2;
                PanelInput = ChannelId.PanelInput_2;
                PanelInputType = PanelInputType_2;
                MonInput = PanelInput_2;
                MinInput = MinPanelInput_2;
                MaxInput = MaxPanelInput_2;
                MinInputF = MinPanelInputF_2;
                MaxInputF = MaxPanelInputF_2;
            }

            TextBox.ForeColor = Color.White;
            if (!MonInput) Panel.Visible = false;

            if ( PanelInputType == vp_type.vp_byte && byte.TryParse(TextBox.Text, out InputValueByte)
                 && (InputValueByte >= MinInput && InputValueByte <= MaxInput))
            {
                if (port.IsConnected) port.Send((byte)PanelInput, vp_type.vp_byte, InputValueByte);
            }
            else if ( PanelInputType == vp_type.vp_int && Int16.TryParse(TextBox.Text, out InputValueShort)
                      && (InputValueShort >= MinInput && InputValueShort <= MaxInput))
            {
                if (port.IsConnected) port.Send((byte)PanelInput, vp_type.vp_int, InputValueShort);
            }
            else if ( PanelInputType == vp_type.vp_uint && UInt16.TryParse(TextBox.Text, out InputValueUShort)
                      && (InputValueUShort >= MinInput && InputValueUShort <= MaxInput))
            {
                if (port.IsConnected) port.Send((byte)PanelInput, vp_type.vp_uint, InputValueUShort);
            }
            else if ( PanelInputType == vp_type.vp_long && Int32.TryParse(TextBox.Text, out InputValueLong)
                      && (InputValueLong >= MinInput && InputValueLong <= MaxInput))
            {
                if (port.IsConnected) port.Send((byte)PanelInput, vp_type.vp_long, InputValueLong);
            }
            else if (PanelInputType == vp_type.vp_ulong && UInt32.TryParse(TextBox.Text, out InputValueULong)
                      && (InputValueULong >= MinInput && InputValueULong <= MaxInput))
            {
                if (port.IsConnected) port.Send((byte)PanelInput, vp_type.vp_ulong, InputValueULong);
            }
            else if (PanelInputType == vp_type.vp_float && float.TryParse(TextBox.Text, out InputValueFloat)
                      && (InputValueFloat >= MinInputF && InputValueFloat <= MaxInputF))
            {
                if (port.IsConnected) port.Send((byte)PanelInput, InputValueFloat);
            }
            else if (PanelInputType == vp_type.vp_string && TextBox.Text.Length <= 35 
                      && (TextBox.Text.Length >= MinInput && TextBox.Text.Length <= MaxInput))
            { 
                if (port.IsConnected) port.Send((byte)PanelInput, TextBox.Text);
            }
            else
            {
                TextBox.ForeColor = Color.Red;
                Panel.Visible = true;
                Valid = false;
            }

            if (Valid)
            {
                if (sender == PanelSendInput_1)
                {
                    PanelInputText_1 = TextBox.Text;
                }
                if (sender == PanelSendInput_1)
                {
                    PanelInputText_2 = TextBox.Text;
                }
            }

            AcceptButton = null;
            CancelButton = null;
        }

        private void PanelDiscardInput_Click(object sender, EventArgs e)
        {
            if (sender == PanelDiscardInput_1)
            {
                if (!PanelInput_1) PanelInputPanel_1.Visible = false;
                if (port.IsConnected) port.Send((byte)ChannelId.PanelInput_1);
                PanelInputTextBox_1.Text = PanelInputText_1;
                PanelInputTextBox_1.ForeColor = Color.White;
            }
            if (sender == PanelDiscardInput_2)
            {
                if (!PanelInput_2) PanelInputPanel_2.Visible = false;
                if (port.IsConnected) port.Send((byte)ChannelId.PanelInput_2);
                PanelInputTextBox_2.Text = PanelInputText_2;
                PanelInputTextBox_2.ForeColor = Color.White;
            }
            AcceptButton = null;
            CancelButton = null;
        }

        private void infoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (info.Visible == true)
            {
                info.Visible = false;
            }
            else
            {
                info.Location = new Point(Location.X + Width, Location.Y);
                info.Visible = true;
            }
        }

        private void ScrollBar5_Scroll(object sender, ScrollEventArgs e)
        {
            Tuple<ChannelId, Control> channel = panelControlList.Find(t => t.Item2 == sender);
            if (channel != null)
            {
                HScrollBar temp = (HScrollBar)channel.Item2;
                int Value = e.NewValue;
                if (port.IsConnected) port.Send((byte)channel.Item1, vp_type.vp_int, Value);
            }
        }

        private Point PreviousLocation { get; set; }

        private void VirtualPanelForm_Move(object sender, EventArgs e)
        {
            if (info.Visible == true)
                info.Location = new Point(Location.X + (info.Location.X - PreviousLocation.X), Location.Y + (info.Location.Y - PreviousLocation.Y));

            if (graph.Visible == true)
                graph.Location = new Point(Location.X + (graph.Location.X - PreviousLocation.X), Location.Y + (graph.Location.Y - PreviousLocation.Y));

            if (stats.Visible == true)
                stats.Location = new Point(Location.X + (stats.Location.X - PreviousLocation.X), Location.Y + (stats.Location.Y - PreviousLocation.Y));

            if (settings.Visible == true)
                settings.Location = new Point(Location.X + (settings.Location.X - PreviousLocation.X), Location.Y + (settings.Location.Y - PreviousLocation.Y));

            PreviousLocation = new Point(Location.X, Location.Y);
        }

        private void filesToDisk_Tick(object sender, EventArgs e)
        {
            FileHandle_1.toDisk();
            FileHandle_2.toDisk();
            FileHandle_3.toDisk();
            FileHandle_4.toDisk();
        }

        private void ShowMsgErr_Tick(object sender, EventArgs e)
        {
            ShowMsgErr.Enabled = false;
            if (port.IsConnected)
            {
                connected_box.BackColor = Color.Lime;
            }
        }
    }
}
