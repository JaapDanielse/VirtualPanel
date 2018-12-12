using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

using ArduinoCom;

namespace VirtualPanel
{
    public partial class GraphForm : Form
    {

        int GridCount = 10;
        int GraphWidth = 0;
        int GraphHeight = 0;
        bool Grid = false;
        bool Hold = false;

        private List<Tuple<ChannelId, Control>> pannelControlList;

        Graph GraphPlot_1;
        Graph GraphPlot_2;
        Graph GraphPlot_3;
        Graph GraphPlot_4;
        Graph GraphPlot_5;

        Rectangle GridRectangle = new Rectangle(0, 0, 263, 220);

        Imagic PersistentDrawing = new Imagic();

        int DrawPenSize = 1;

        string GraphCaption1Text = "";
        string GraphCaption2Text = "";

        Color DrawTextColor = Color.White;
        Color DrawColor    = Color.White;

        Point DrawtextPoint = new Point(0, 0);
        Point LinePoint = new Point(0, 0);
        bool LinePointValid = false;

        private ArduinoPort arduinoport;

        public GraphForm(ArduinoPort port)
        {
            arduinoport = port;
            InitializeComponent();

            GraphPlot_1 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_2 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_3 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_4 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_5 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));


            GraphPlot_1.Color = Color.White;
            GraphPlot_2.Color =  Color.Yellow;
            GraphPlot_3.Color =  Color.Orange;
            GraphPlot_4.Color =  Color.Red;
            GraphPlot_5.Color = Color.DodgerBlue;

            pannelControlList = new List<Tuple<ChannelId, Control>>();
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.GraphButton_1, graphButton1));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.GraphButton_2, graphButton2));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.GraphButton_3, graphButton3));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.GraphButton_4, graphButton4));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.GraphLabel_1, graphLabel1));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.GraphLabel_2, graphLabel2));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.GraphLabel_3, graphLabel3));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.GraphLabel_4, graphLabel4));
            pannelControlList.Add(new Tuple<ChannelId, Control>(ChannelId.GraphLabel_5, graphLabel5));

            arduinoport.MessageReceived += Arduinoport_MessageReceived;
            //GraphPanelClear();

            foreach (var tuple in pannelControlList)
            {
                tuple.Item2.Visible = false;
            }
            PenColor1.Visible = false;
            PenColor2.Visible = false;
            PenColor3.Visible = false;
            PenColor4.Visible = false;
            PenColor5.Visible = false;
        }

        public void GraphPanelClear()
        {
            graphButton1.Text = "";

            graphButton2.Text = "";
            graphButton3.Text = "";
            graphButton4.Text = "";
            graphButton1.Visible = false;
            graphButton2.Visible = false;
            graphButton3.Visible = false;
            graphButton4.Visible = false;
            graphLabel1.Text = "";
            graphLabel2.Text = "";
            graphLabel3.Text = "";
            graphLabel4.Text = "";
            graphLabel5.Text = "";
            graphLabel1.Visible = false;
            graphLabel2.Visible = false;
            graphLabel3.Visible = false;
            graphLabel4.Visible = false;
            graphLabel5.Visible = false;
            GraphCaption1Text = "";
            GraphCaption2Text = "";
            DrawPenSize = 1;
            DrawTextColor = Color.White;
            DrawColor = Color.White;

            PenColor1.Visible = false;
            PenColor2.Visible = false;
            PenColor3.Visible = false;
            PenColor4.Visible = false;
            PenColor5.Visible = false;
            Grid = false;
            GridCount = 10;
            GraphPlot_1 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_2 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_3 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_4 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_5 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_1.Color = Color.Yellow;
            GraphPlot_2.Color = Color.Orange;
            GraphPlot_3.Color = Color.Red;
            GraphPlot_4.Color = Color.DodgerBlue;
            GraphPlot_5.Color = Color.Lime;
            PersistentDrawing.Clear();
            Hold = false;

        }


        private void Arduinoport_MessageReceived(object sender, MessageEventArgs<object> mse)
        {
            ChannelId id = (ChannelId)mse.ChannelID;

            Tuple<ChannelId, Control> control = pannelControlList.Find(t => t.Item1 == id);

            if (!Hold)
            {
                if (control != null)
                {
                    if (control.Item2 is Button) VirtualPanelForm.SetButtonAppearance((Button)control.Item2, mse);
                    if (control.Item2 is Label) SetLabelAppearance((Label)control.Item2, mse);
                }

                if ((ChannelId)mse.ChannelID == ChannelId.Graph && mse.Type == vp_type.vp_string)
                {
                    if ((string)mse.Data == "$CLEAR") { PersistentDrawing.Clear(); }
                }
                if ((ChannelId)mse.ChannelID == ChannelId.GraphPen && mse.Type == vp_type.vp_string) SetDrawPen((string)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawLine && mse.Type == vp_type.vp_ulong) DrawPersitentLine((Int64)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawLine && mse.Type == vp_type.vp_uint) DrawLinePoint((Int32)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawLine && mse.Type == vp_type.vp_void) LinePointValid = false;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawPixel && mse.Type == vp_type.vp_uint) DrawPixel((Int32)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphText && mse.Type == vp_type.vp_uint) DrawTextPos((Int32)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphText && mse.Type == vp_type.vp_string) Drawtext((string)mse.Data);

                //if ((ChannelId)mse.ChannelID == ChannelId.GraphSampleCount && mse.Type == vp_type.vp_int)
                //{
                //    GraphPlot_1.SampleCount = (Int32)mse.Data;
                //    GraphPlot_2.SampleCount = (Int32)mse.Data;
                //    GraphPlot_3.SampleCount = (Int32)mse.Data;
                //    GraphPlot_4.SampleCount = (Int32)mse.Data;
                //    GraphPlot_5.SampleCount = (Int32)mse.Data;
                //}

                if ((ChannelId)mse.ChannelID == ChannelId.GraphGrid && mse.Type == vp_type.vp_boolean) Grid = (bool)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphGrid && mse.Type == vp_type.vp_int) { Grid = true; GridCount = (int)mse.Data; }

                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_1 && mse.Type == vp_type.vp_string) SetGraphAttr((string)mse.Data, GraphPlot_1);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_2 && mse.Type == vp_type.vp_string) SetGraphAttr((string)mse.Data, GraphPlot_2);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_3 && mse.Type == vp_type.vp_string) SetGraphAttr((string)mse.Data, GraphPlot_3);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_4 && mse.Type == vp_type.vp_string) SetGraphAttr((string)mse.Data, GraphPlot_4);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_5 && mse.Type == vp_type.vp_string) SetGraphAttr((string)mse.Data, GraphPlot_5);

                if ((ChannelId)mse.ChannelID == ChannelId.GraphValueCount_1 && mse.Type == vp_type.vp_int) GraphPlot_1.SampleCount = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValueCount_2 && mse.Type == vp_type.vp_int) GraphPlot_2.SampleCount = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValueCount_3 && mse.Type == vp_type.vp_int) GraphPlot_3.SampleCount = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValueCount_4 && mse.Type == vp_type.vp_int) GraphPlot_4.SampleCount = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValueCount_5 && mse.Type == vp_type.vp_int) GraphPlot_5.SampleCount = (int)mse.Data;

                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_1 && mse.Type == vp_type.vp_byte) { GraphValueAdd((int)mse.Data, GraphPlot_1); Grid = true; }
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_2 && mse.Type == vp_type.vp_byte) { GraphValueAdd((int)mse.Data, GraphPlot_2); Grid = true; }
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_3 && mse.Type == vp_type.vp_byte) { GraphValueAdd((int)mse.Data, GraphPlot_3); Grid = true; }
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_4 && mse.Type == vp_type.vp_byte) { GraphValueAdd((int)mse.Data, GraphPlot_4); Grid = true; }
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_5 && mse.Type == vp_type.vp_byte) { GraphValueAdd((int)mse.Data, GraphPlot_5); Grid = true; }

                if ((ChannelId)mse.ChannelID == ChannelId.GraphCaption_1 && mse.Type == vp_type.vp_string) GraphCaption1Text = (string)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphCaption_2 && mse.Type == vp_type.vp_string) GraphCaption2Text = (string)mse.Data;

                GraphPictureBox1.Invalidate();
            }
        }

        private void SetGraphAttr(string data, Graph GraphPlot)
        {
            Color col = VirtualPanelForm.String2Color(data);
            if (!col.IsEmpty)
                GraphPlot.Color = col; //
            else
            {
                if (data == "$ROLLING") GraphPlot.Type = GraphType.Rolling;
                if (data == "$STATIC") GraphPlot.Type = GraphType.Static;
            }
        }

        private void Drawtext(string data)
        {
            Color col = VirtualPanelForm.String2Color(data);
            if (!col.IsEmpty)
                DrawTextColor = col; //
            else
            {
                PersistentDrawing.Add(new Text(DrawtextPoint, data, DrawTextColor, 8));
                GraphPictureBox1.Invalidate();
            }
        }

        private void DrawTextPos(int data)
        {
            string hexdata = "";
            int x = 0;
            int y = 0;
            hexdata = Convert.ToUInt16(data).ToString("X4");
            x = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(0, 2), 16)))+4;
            y = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(2, 2), 16)));
            y = GraphPictureBox1.Height - y;

            if (DrawColor == Color.Black)
                DrawtextPoint = new Point(x, y);
            else
            DrawtextPoint = new Point(x, y);
        }

        private void DrawPersitentLine(Int64 MyLine)
        {
            String hexdata = "";
            int xs = 0;
            int ys = 0;
            int xe = 0;
            int ye = 0;

            hexdata = Convert.ToUInt32(MyLine).ToString("X8");
            xs = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(0, 2), 16)))+4;
            ys = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(2, 2), 16)));
            xe = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(4, 2), 16)))+4;
            ye = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(6, 2), 16)));
            ys = GraphPictureBox1.Height - ys;
            ye = GraphPictureBox1.Height - ye;

            if (DrawColor == Color.Black)
                PersistentDrawing.Delete(new Line(xs, ys, xe, ye, DrawColor, DrawPenSize));
            else
            PersistentDrawing.Add(new Line(xs, ys, xe, ye, DrawColor, DrawPenSize));
            GraphPictureBox1.Invalidate();
        }

        private void DrawLinePoint(int data)
        {
            Point DrawPoint;

            string hexdata = "";
            int x = 0;
            int y = 0;

            hexdata = Convert.ToUInt16(data).ToString("X4");
            x = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(0, 2), 16)))+4;
            y = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(2, 2), 16)));
            y = GraphPictureBox1.Height - y;

            DrawPoint = new Point(x, y);

            if (LinePointValid)
            {
                if (DrawColor == Color.Black)
                    PersistentDrawing.Delete(new Line(LinePoint, DrawPoint, DrawColor, DrawPenSize));
                else
                PersistentDrawing.Add(new Line(LinePoint, DrawPoint, DrawColor, DrawPenSize));

                GraphPictureBox1.Invalidate();
                LinePoint = DrawPoint;
            }
            else
            {
                LinePoint = new Point(x, y);
                LinePointValid = true;
            }
        }

        private void DrawPixel(int Data)
        {
            Point DrawPoint;

            string hexdata = "";
            int x = 0;
            int y = 0;
            hexdata = Convert.ToUInt16(Data).ToString("X4");
            x = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(0, 2), 16)));
            y = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(2, 2), 16)));
            y = GraphPictureBox1.Height - y;

            DrawPoint = new Point(x, y);

            if (DrawColor == Color.Black)
                PersistentDrawing.Delete(new Pixel(DrawPoint.X, DrawPoint.Y, DrawColor));
            else
            PersistentDrawing.Add(new Pixel(DrawPoint.X, DrawPoint.Y, DrawColor));

            GraphPictureBox1.Invalidate();
        }

        private void SetDrawPen(string PenColor)
        {
            Color col = VirtualPanelForm.String2Color(PenColor);
            if (!col.IsEmpty) DrawColor = col; //
            if (PenColor == "$1PX") DrawPenSize = 1;
            if (PenColor == "$2PX") DrawPenSize = 2;
            if (PenColor == "$3PX") DrawPenSize = 3;
            if (PenColor == "$4PX") DrawPenSize = 4;
        }

        private void SetLabelAppearance(Label control, MessageEventArgs<object> mse)
        {
            PictureBox p = null;

            control.Visible = true;

            if (control == graphLabel1) p = PenColor1;
            if (control == graphLabel2) p = PenColor2;
            if (control == graphLabel3) p = PenColor3;
            if (control == graphLabel4) p = PenColor4;
            if (control == graphLabel5) p = PenColor5;

            if (mse.Type == vp_type.vp_boolean)
            {
                if (!(bool)mse.Data) control.Visible = false;
            }
            else if (mse.Type == vp_type.vp_string)
            {
                Color col = VirtualPanelForm.String2Color((string)mse.Data);
                if (!col.IsEmpty) { p.BackColor = col; p.Visible = true; }
                else if ((string)mse.Data == "$OFF") { p.Visible = false; }
                else control.Text = (string)mse.Data;
            }
            else
                control.Text = mse.Data.ToString();
          }


        private void GraphValueAdd(int Value, Graph GraphPlot)
        {
            GraphPlot.AddValue(255 - Value);
        }

        private void GraphForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Visible = false;
            e.Cancel = true;
        }

        private void GraphPictureBox1_Paint(object sender, PaintEventArgs e)
        {
            GraphWidth = GraphPictureBox1.Size.Width;
            GraphHeight = GraphPictureBox1.Size.Height;

            Graphics g = e.Graphics;
            Pen mypen = new Pen(Color.DimGray, 1);

            if (Grid)
            {
                for (int i = 0; i <= GridCount + 1; i++)
                {
                    float lineY = i * (GraphHeight / (float)GridCount);
                    g.DrawLine(mypen, 0.0f, lineY, GraphWidth, lineY);
                }

               int HGridCount = (int)(GridCount * 1.2);

                for (int i = 0; i <= HGridCount + 1; i++)
               {
                    float lineX = i * (GraphWidth / (float)HGridCount);
                    g.DrawLine(mypen, lineX, 0.0f, lineX, GraphHeight);
               }
                }

            g.DrawString(GraphCaption1Text, new Font("Verdana", 8), new SolidBrush(DrawTextColor), new Point(10, 5));
            g.DrawString(GraphCaption2Text, new Font("Verdana", 8), new SolidBrush(DrawTextColor), new Point(10, 205));

            GraphPlot_1.Draw(g);
            GraphPlot_2.Draw(g);
            GraphPlot_3.Draw(g);
            GraphPlot_4.Draw(g);
            GraphPlot_5.Draw(g);

            PersistentDrawing.Draw(g);
        }


        private long Map(long x, long in_min, long in_max, long out_min, long out_max)
        {
            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        }

        private void GraphHoldButton_Click(object sender, EventArgs e)
        {
            Hold = !Hold;
            if (Hold) GraphHoldButton.Text = "resume"; else GraphHoldButton.Text = "hold";
        }

        private void GraphImageDialogButton_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                Bitmap png = new Bitmap(GraphPictureBox1.Width, GraphPictureBox1.Height);
                GraphPictureBox1.DrawToBitmap(png, GraphPictureBox1.ClientRectangle);
                png.Save(saveFileDialog1.FileName);
            }
        }


        private void button_Click(object sender, EventArgs e)
        {
            Tuple<ChannelId, Control> channel = pannelControlList.Find(t => t.Item2 == sender);
            if (channel != null)
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)channel.Item1);

                if (VirtualPanelForm.StaticDisplay && arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.StaticDisplay);
            }
        }
    }
}
