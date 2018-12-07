using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Media;
using System.Windows.Forms;

using ArduinoCom;

namespace VirtualPanel
{
     public enum ChannelId
    {
        //
        ApplicationName, // ApplicationName
        PanelConnected,  // PannelConnected
        Reset,           // Reset
        StaticDisplay,   // StaticDisplay
        DynamicDisplay,  // DynamicDisplay
        UnixTime,        // UnixTime
        PanelColor,      // Panel
        Pling,           // Pling
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
        ScrollBar_1, // ScrollBar_1
        ScrollBar_2, // ScrollBar_2
        ScrollBar_3, // ScrollBar_3
        ScrollBar_4, // ScrollBar_4
        //
        MaxScrollBar_1, // MaxScrollBar_1
        MaxScrollBar_2, // MaxScrollBar_2
        MaxScrollBar_3, // MaxScrollBar_3
        MaxScrollBar_4, // MaxScrollBar_4
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
        Monitor,        // Monitor
        MonitorField_1, // MonitorField_1
        MonitorField_2, // MonitorField_2
        MonitorField_3, // MonitorField_3
        MonitorField_4, // MonitorField_4
        MonitorField_5, // MonitorField_5
        MonitorField_6, // MonitorField_6
        //
        MonitorScrollBox,  // StatMonitor
        //
        Graph, // false/true, byte (1(draw), 2(stat), 3(run)
        GraphGrid, // byte number of segments
        GraphSampleCount, // byte 
        GraphPen, // $FINE, $THICK, $RED, $GREEN, $YELLOW, $ORANGE, $WHITE, $BLUE 
        GraphDrawLine, // ULong 4x byte (Fx,Fy,Tx,Ty) UInt 2 x byte (X,Y)
        GraphDrawPixel, // UInt 2 x byte (X,Y)
        GraphText, //
        //
        GraphValue_1, // byte 
        GraphValue_2, // byte 
        GraphValue_3, // byte 
        GraphValue_4, // byte 
        GraphValue_5, // byte 
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
        GraphButton_4  //
        //
    }

    public partial class VirtualPanelForm : Form
    {
        private MsgLogForm settings;
        private MonitorForm stats;
        private GraphForm graph;
        private ArduinoPort port;
        private List<Tuple<ChannelId, Control>> pannelControlList;
        public static Boolean StaticDisplay = false;
        int MsgNum = 0;


        public VirtualPanelForm()
        {
            InitializeComponent();

            pannelControlList = new List<Tuple<ChannelId, Control>>();

            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_1, button1));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_2, button2));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_3, button3));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_4, button4));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_5, button5));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_6, button6));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_7, button7));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_8, button8));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_9, button9));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_10, button10));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_11, button11));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_12, button12));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_13, button13));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_14, button14));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_15, button15));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_16, button16));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Button_17, button17));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_1, Led1));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_2, Led2));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_3, Led3));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_4, Led4));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_5, Led5));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_6, Led6));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_7, Led7));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_8, Led8));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_9, Led9));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_10, Led10));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_11, Led11));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_12, Led12));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Led_13, Led13));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.ApplicationName, ApplicationTitle));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Display_1, display1));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Display_2, display2));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Display_3, display3));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.Display_4, display4));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.ScrollBar_1, ScrollBar1));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.ScrollBar_2, ScrollBar2));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.ScrollBar_3, ScrollBar3));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.ScrollBar_4, ScrollBar4));

            port = new ArduinoPort("[PANEL01V01]");

            stats = new MonitorForm(port);
            stats.Show();
            stats.Visible = false;

            settings = new MsgLogForm(port);
            settings.Show();
            settings.Visible = false;

            graph = new GraphForm(port);
            graph.Show();
            graph.Visible = false;

            Panel_Reset();
            panel1.Visible = false;

            port.Connected += Port_Connected;
            port.Disconnected += Port_Disconnected;
            port.MessageReceived += Port_MessageReceived;
            port.Open();
            connected_box.BackColor = Color.DarkGreen;
        }

        private void Panel_Reset()
        {
            stats.Visible = false;
            settings.Visible = false;
            graph.Visible = false;

            foreach (var t in pannelControlList)
            {
                t.Item2.Visible = false;
                t.Item2.ForeColor = Color.Black;
            }

            panel1.Visible = false;

            settings.LogFormClear();
            stats.MonitorClear();
            graph.GraphPanelClear();

            scrolllabel1.Visible = false;
            scrolllabel2.Visible = false;
            scrolllabel3.Visible = false;
            scrolllabel4.Visible = false;


            ApplicationTitle.ForeColor = Color.White;

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

            button3.Select();
            StaticDisplay = false;
            timer1.Enabled = false;
            timer1.Interval = 500;
            panel1.Visible = true;

            if (port.IsConnected) port.Send((byte)ChannelId.PanelConnected);
            if (port.IsConnected) port.Send((byte)ChannelId.StaticDisplay);
        }

        private void Port_Disconnected(object sender, ConnectedEventArgs e)
        {
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

            Tuple<ChannelId, Control> control = pannelControlList.Find(t => t.Item1 == id);

            if (control != null)
                SetAppearance(control.Item2, mse);
            else
            {
                if (id == ChannelId.UnixTime) SendUnixTime(mse);
                if (id == ChannelId.StaticDisplay  && mse.Type == vp_type.vp_boolean) StaticDisplay  = (bool)mse.Data;
                if (id == ChannelId.DynamicDisplay && mse.Type == vp_type.vp_boolean) timer1.Enabled = (bool)mse.Data;

                if (id == ChannelId.DynamicDisplay && mse.Type == vp_type.vp_int)
                {
                    if ((int)mse.Data >= 100 && (int)mse.Data <= 1000) timer1.Interval = (int)mse.Data;
                    timer1.Enabled = true;
                }

                if (id == ChannelId.Pling) SystemSounds.Asterisk.Play();

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

                if (id == ChannelId.Reset) Panel_Reset();
                if (id == ChannelId.MaxScrollBar_1 && mse.Type == vp_type.vp_int) ScrollBar1.Maximum = (int)mse.Data + 9;
                if (id == ChannelId.MaxScrollBar_2 && mse.Type == vp_type.vp_int) ScrollBar2.Maximum = (int)mse.Data + 9;
                if (id == ChannelId.MaxScrollBar_3 && mse.Type == vp_type.vp_int) ScrollBar3.Maximum = (int)mse.Data + 9;
                if (id == ChannelId.MaxScrollBar_4 && mse.Type == vp_type.vp_int) ScrollBar4.Maximum = (int)mse.Data + 9;
            }
        }

        private void SetAppearance(Control control, MessageEventArgs<object> mse)
        {
            if (control is Button) SetButtonAppearance((Button)control, mse);
            if (control is PictureBox) SetLedAppearance((PictureBox)control, mse);
            if (control is Label) SetDisplayAppearance((Label)control, mse);
            if (control is VScrollBar) SetScrollBarAppearance((VScrollBar)control, mse);
        }

        public static Color String2Color(string ColorString)
        {
            Color convertedColor = Color.Empty;

            if (ColorString == "$YELLOW") convertedColor = Color.Yellow;
            if (ColorString == "$ORANGE") convertedColor = Color.Orange;
            if (ColorString == "$RED")   convertedColor = Color.Red;
            if (ColorString == "$BLUE")  convertedColor = Color.DodgerBlue;
            if (ColorString == "$GREEN") convertedColor = Color.Lime;
            if (ColorString == "$BLACK") convertedColor = Color.Black;
            if (ColorString == "$WHITE") convertedColor = Color.White;
            if (ColorString == "$BLACK") convertedColor = Color.Black;
            if (ColorString == "$OFF") convertedColor = Color.Black;
            if (ColorString == "$DEL") convertedColor = Color.Black;

            return convertedColor;
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
                else if ((string)mse.Data == "$LEFT")
                {
                    button.Font = new Font("Wingdings 3", 10);
                    button.Text = "";
                }
                else if ((string)mse.Data == "$UP")
                {
                    button.Font = new Font("Wingdings 3", 10);
                    button.Text = "";
                }
                else if ((string)mse.Data == "$DOT")
                {
                    button.Font = new Font("Wingdings", 11);
                    button.Text = "";
                }
                else if ((string)mse.Data == "$DOWN")
                {
                    button.Font = new Font("Wingdings 3", 10);
                    button.Text = "";
                }
                else if ((string)mse.Data == "$RIGHT")
                {
                    button.Font = new Font("Wingdings 3", 10);
                    button.Text = "";
                }
                else if ((string)mse.Data == "$SET")
                {
                    button.Font = new Font("Wingdings 2", 10);
                    button.Text = "";
                }
                else if ((string)mse.Data == "$ONOFF")
                {
                    button.Font = new Font("Wingdings 2", 8);
                    button.Text = "";
                }
                else if ((string)mse.Data == "$LTURN")
                {
                    button.Font = new Font("Wingdings 3", 11);
                    button.Text = "";
                }
                else if ((string)mse.Data == "$RTURN")
                {
                    button.Font = new Font("Wingdings 3", 11);
                    button.Text = "";
                }
                else if ((string)mse.Data == "$RUN")
                {
                    button.Font = new Font("Wingdings 3", 10);
                    button.Text = "";
                }
                else if ((string)mse.Data == "$PAUSE")
                {
                    button.Font = new Font("Arial", 8);
                    button.Text = " ▌▌";
                }
                else if ((string)mse.Data == "$STOP")
                {
                    button.Font = new Font("Wingdings 2", 11);
                    button.Text = "";
                }
                else
                {
                    button.Font = new Font("Microsoft Sans Serif", 8);
                    button.Text = (string)mse.Data;
                }
            }
            else
            {
                button.Font = new Font("Microsoft Sans Serif", 8);
                button.Text = mse.Data.ToString();
            }
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
                if (!(bool)mse.Data) display.Visible = false;
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
                else
                    display.Text = (string)mse.Data;
            }
            else
                display.Text = mse.Data.ToString();
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
                        if ((int)mse.Data <= (ScrollBar1.Maximum - 9) && (int)mse.Data >= 0)
                            ScrollBar1.Value = ((ScrollBar1.Maximum - 9) - (int)mse.Data);
                    if (scrollBar.Name == "ScrollBar2")
                        if ((int)mse.Data <= (ScrollBar2.Maximum - 9) && (int)mse.Data > 0)
                            ScrollBar2.Value = ((ScrollBar2.Maximum - 9) - (int)mse.Data);
                    if (scrollBar.Name == "ScrollBar3")
                        if ((int)mse.Data <= (ScrollBar3.Maximum - 9) && (int)mse.Data >= 0)
                            ScrollBar3.Value = ((ScrollBar3.Maximum - 9) - (int)mse.Data);
                    if (scrollBar.Name == "ScrollBar4")
                        if ((int)mse.Data <= (ScrollBar4.Maximum - 9) && (int)mse.Data >= 0)
                            ScrollBar4.Value = ((ScrollBar4.Maximum - 9) - (int)mse.Data);
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
            Tuple<ChannelId, Control> channel = pannelControlList.Find(t => t.Item2 == sender);
            if (channel != null)
            {
                if (port.IsConnected) port.Send((byte)channel.Item1);

                if (StaticDisplay && port.IsConnected) port.Send((byte)ChannelId.StaticDisplay);
            }
        }


        private void timer1_Tick(object sender, EventArgs e)
        {

            if (port.IsConnected) port.Send((byte)ChannelId.DynamicDisplay);
        }

        private void ScrollBar_Scroll(object sender, ScrollEventArgs e)
        {
            Tuple<ChannelId, Control> channel = pannelControlList.Find(t => t.Item2 == sender);
            if (channel != null)
            {
                VScrollBar temp = (VScrollBar)channel.Item2;
                int Value = (temp.Maximum - 9) - temp.Value ;
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
            if (port.IsConnected)
            {
                port.Close();
                connected_box.BackColor = Color.Black;
            }
            else
            {
                port.Open();
                connected_box.BackColor = Color.DarkGreen;
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
            pictureBox2.BackColor = Color.LightBlue;
        }


        private void mouseLeave(object sender, EventArgs e)
        {
            pictureBox2.BackColor = Color.CornflowerBlue;
        }

        private void resetArduinoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            port.Reset();
        }
    }
}
