using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace VirtualPanel
{
    public partial class GraphForm : Form
    {

        int GridCount = 0;
        int SampleCount = 50;
        int GraphWidth = 0;
        int GraphHeight = 0;

        int VMarginSpace = 0;
        int GridSize = 0;
        int HMarginSpace = 0;
        bool Hold = false;
        private List<Tuple<ChannelId, Control>> pannelControlList;

        List<int> GraphValues_1 = new List<int>();
        List<int> GraphValues_2 = new List<int>();
        List<int> GraphValues_3 = new List<int>();
        List<int> GraphValues_4 = new List<int>();
        List<int> GraphValues_5 = new List<int>();

        int DrawPenSize = 1;

        string GraphCaption1Text = "";
        string GraphCaption2Text = "";

        Color DrawTextColor = Color.White;
        Color DrawColor = Color.White;
        Color PlotColor_1 = Color.Yellow;
        Color PlotColor_2 = Color.Orange;
        Color PlotColor_3 = Color.Red;
        Color PlotColor_4 = Color.DodgerBlue;
        Color PlotColor_5 = Color.Lime;

        Point DrawtextPoint = new Point(0, 0);
        Point LinePoint = new Point(0, 0);
        bool LinePointValid = false;

        private ArduinoPort arduinoport;

        public GraphForm(ArduinoPort port)
        {
            arduinoport = port;
            InitializeComponent();

            //DrawPersitentLine(new Point(0, 0), new Point(200, 200));

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
            graphLabel1.Text = "";
            graphLabel2.Text = "";
            graphLabel3.Text = "";
            graphLabel4.Text = "";
            graphLabel5.Text = "";
            GraphCaption1Text = "";
            GraphCaption2Text = "";
            DrawPenSize = 1;
            DrawTextColor = Color.White;
            DrawColor = Color.White;
            PlotColor_1 = Color.Yellow;
            PlotColor_2 = Color.Orange;
            PlotColor_3 = Color.Red;
            PlotColor_4 = Color.DodgerBlue;
            PlotColor_5 = Color.Lime;
            GraphValues_1.Clear();
            GraphValues_2.Clear();
            GraphValues_3.Clear();
            GraphValues_4.Clear();
            GraphValues_5.Clear();
            GridCount = 0;
            SampleCount = 50;
            GridSize = 0;
            Hold = false;

        }


        private void Arduinoport_MessageReceived(object sender, MessageEventArgs mse)
        {
            ChannelId id = (ChannelId)mse.ChannelID;

            Tuple<ChannelId, Control> control = pannelControlList.Find(t => t.Item1 == id);

            if (control != null)
            {
                if (control.Item2 is Button) VirtualPanelForm.SetButtonAppearance((Button)control.Item2, mse);
                if (control.Item2 is Label) SetLabelAppearance((Label)control.Item2, mse);
            }

            if ((ChannelId)mse.ChannelID == ChannelId.GraphPen && mse.Type == vp_type.vp_string) SetDrawPen((string)mse.Data);
            if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawLine && mse.Type == vp_type.vp_ulong) DrawPersitentLine((Int64)mse.Data);
            if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawLine && mse.Type == vp_type.vp_uint) DrawLinePoint((Int32)mse.Data);
            if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawLine && mse.Type == vp_type.vp_void) LinePointValid = false;
            if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawPixel && mse.Type == vp_type.vp_uint) DrawPixel((Int32)mse.Data);
            if ((ChannelId)mse.ChannelID == ChannelId.GraphText && mse.Type == vp_type.vp_uint) DrawTextPos((Int32)mse.Data);
            if ((ChannelId)mse.ChannelID == ChannelId.GraphText && mse.Type == vp_type.vp_string) Drawtext((string)mse.Data);

            if ((ChannelId)mse.ChannelID == ChannelId.GraphGrid && mse.Type == vp_type.vp_int) GridCount = (int)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.GraphCaption_1 && mse.Type == vp_type.vp_string) GraphCaption1Text = (string)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.GraphCaption_2 && mse.Type == vp_type.vp_string) GraphCaption2Text = (string)mse.Data;
            if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_1 && mse.Type == vp_type.vp_byte) GraphValueAdd((int)mse.Data, GraphValues_1);
            if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_2 && mse.Type == vp_type.vp_byte) GraphValueAdd((int)mse.Data, GraphValues_2);
            if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_3 && mse.Type == vp_type.vp_byte) GraphValueAdd((int)mse.Data, GraphValues_3);
            if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_4 && mse.Type == vp_type.vp_byte) GraphValueAdd((int)mse.Data, GraphValues_4);
            if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_5 && mse.Type == vp_type.vp_byte) GraphValueAdd((int)mse.Data, GraphValues_5);
            if (!Hold) GraphPictureBox1.Invalidate();
        }

        private void Drawtext(string data)
        {
            Color col = VirtualPanelForm.String2Color(data);
            if (!col.IsEmpty)
                DrawTextColor = col; //
            else
            {
                Graphics g = GraphPictureBox1.CreatePersistentGraphics();
                g.DrawString(data, new Font("Verdana", 8), new SolidBrush(DrawTextColor), DrawtextPoint);
                GraphPictureBox1.Invalidate();
                g.Dispose();
            }
        }

        private void DrawTextPos(int data)
        {
            string hexdata = "";
            int x = 0;
            int y = 0;
            hexdata = Convert.ToUInt16(data).ToString("X4");
            x = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(0, 2), 16)));
            y = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(2, 2), 16)));
            y = GraphPictureBox1.Height - y;

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
            xs = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(0, 2), 16)));
            ys = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(2, 2), 16)));
            xe = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(4, 2), 16)));
            ye = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(6, 2), 16)));
            ys = GraphPictureBox1.Height - ys;
            ye = GraphPictureBox1.Height - ye;

            Graphics g = GraphPictureBox1.CreatePersistentGraphics();
            g.DrawLine(new Pen(DrawColor, DrawPenSize), xs, ys, xe, ye);
            GraphPictureBox1.Invalidate();
            g.Dispose();

            LinePoint = new Point(xe, ye);
            LinePointValid = true;
        }

        private void DrawLinePoint(int data)
        {
            Point DrawPoint;

            string hexdata = "";
            int x = 0;
            int y = 0;

            hexdata = Convert.ToUInt16(data).ToString("X4");
            x = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(0, 2), 16)));
            y = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(2, 2), 16)));
            y = GraphPictureBox1.Height - y;

            DrawPoint = new Point(x, y);

            if (LinePointValid)
            {
                Graphics g = GraphPictureBox1.CreatePersistentGraphics();
                g.DrawLine(new Pen(DrawColor, DrawPenSize), LinePoint, DrawPoint);
                LinePoint = DrawPoint;
                g.Dispose();
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

            Graphics g = GraphPictureBox1.CreatePersistentGraphics();
            g.FillRectangle(new SolidBrush(DrawColor), DrawPoint.X, DrawPoint.Y, 1, 1);
            GraphPictureBox1.Invalidate();
            g.Dispose();
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

        private void SetLabelAppearance(Label control, MessageEventArgs mse)
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


        private void GraphValueAdd(int Value, List<int> Valuelist)
        {
            if (Valuelist.Count >= SampleCount) Valuelist.RemoveAt(0);
            Valuelist.Add(Value);
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

            //g.Clear(Color.Black);

            if (GridCount != 0)
            {
                VMarginSpace = (GraphHeight % GridCount);
                GridSize = ((GraphHeight - VMarginSpace) / GridCount);
                HMarginSpace = (GraphWidth % GridSize);

                for (int i = VMarginSpace / 2; i <= GraphHeight - (VMarginSpace / 2); i += GridSize)
                {
                    g.DrawLine(mypen, 0, i, GraphWidth, i);
                }

                for (int i = HMarginSpace / 2; i <= GraphWidth - (HMarginSpace / 2); i += GridSize)
                {
                    g.DrawLine(mypen, i, VMarginSpace / 2, i, GraphHeight - (VMarginSpace / 2) - 1);
                }
            }

            GraphDrawPlot(GraphValues_1, g, PlotColor_1);
            GraphDrawPlot(GraphValues_2, g, PlotColor_2);
            GraphDrawPlot(GraphValues_3, g, PlotColor_3);
            GraphDrawPlot(GraphValues_4, g, PlotColor_4);
            GraphDrawPlot(GraphValues_5, g, PlotColor_5);

            g.DrawString(GraphCaption1Text, new Font("Verdana", 8), new SolidBrush(DrawTextColor), new Point(10, 10));
            g.DrawString(GraphCaption2Text, new Font("Verdana", 8), new SolidBrush(DrawTextColor), new Point(10, 200));

        }


        void GraphDrawPlot(List<int> Valuelist, Graphics g, Color PenColor)
        {
            float XStep = (float)GraphWidth / (SampleCount - 1);
            List<PointF> drawing = new List<PointF>();

            for (int i = 0; i < Valuelist.Count(); i++)
            {
                int GraphValue = GraphHeight - (int)Map(Valuelist[i], 0, 255, VMarginSpace/2, GraphHeight - (VMarginSpace/2));
                drawing.Add(new PointF(i * XStep, GraphValue));
            }
            Pen mypen = new Pen(PenColor, 1);
            if (drawing.Count > 1)
                g.DrawLines(mypen, drawing.ToArray());
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
