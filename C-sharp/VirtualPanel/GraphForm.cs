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

        private vp_type GraphInputType_1 = vp_type.vp_int;
        private vp_type GraphInputType_2 = vp_type.vp_int;
        private vp_type GraphInputType_3 = vp_type.vp_int;
        private vp_type GraphInputType_4 = vp_type.vp_int;
        private vp_type GraphInputType_5 = vp_type.vp_int;

        private bool GraphInputFlag_1 = false;
        private bool GraphInputFlag_2 = false;
        private bool GraphInputFlag_3 = false;
        private bool GraphInputFlag_4 = false;
        private bool GraphInputFlag_5 = false;

        private bool GraphInputEdit_1 = false;
        private bool GraphInputEdit_2 = false;
        private bool GraphInputEdit_3 = false;
        private bool GraphInputEdit_4 = false;
        private bool GraphInputEdit_5 = false;

        private long MinGraphInput_1 = long.MinValue;
        private long MinGraphInput_2 = long.MinValue;
        private long MinGraphInput_3 = long.MinValue;
        private long MinGraphInput_4 = long.MinValue;
        private long MinGraphInput_5 = long.MinValue;

        private long MaxGraphInput_1 = long.MaxValue;
        private long MaxGraphInput_2 = long.MaxValue;
        private long MaxGraphInput_3 = long.MaxValue;
        private long MaxGraphInput_4 = long.MaxValue;
        private long MaxGraphInput_5 = long.MaxValue;

        private float MinGraphInputF_1 = float.MinValue;
        private float MinGraphInputF_2 = float.MinValue;
        private float MinGraphInputF_3 = float.MinValue;
        private float MinGraphInputF_4 = float.MinValue;
        private float MinGraphInputF_5 = float.MinValue;

        private float MaxGraphInputF_1 = float.MaxValue;
        private float MaxGraphInputF_2 = float.MaxValue;
        private float MaxGraphInputF_3 = float.MaxValue;
        private float MaxGraphInputF_4 = float.MaxValue;
        private float MaxGraphInputF_5 = float.MaxValue;

        private string GraphInputText_1 = "";
        private string GraphInputText_2 = "";
        private string GraphInputText_3 = "";
        private string GraphInputText_4 = "";
        private string GraphInputText_5 = "";

        Graph GraphPlot_1;
        Graph GraphPlot_2;
        Graph GraphPlot_3;
        Graph GraphPlot_4;
        Graph GraphPlot_5;

        Rectangle GridRectangle = new Rectangle(0, 0, 263, 220);

        Imagic PersistentDrawing = new Imagic();

        int DrawPenSize = 1;
        int DrawPixelSize = 1;
        int DrawCirclePenSize = 1;

        Color DrawTextColor = Color.White;
        Color DrawLineColor = Color.White;
        Color DrawCircleColor = Color.White;
        Color DrawPointColor = Color.White;

        Point DrawtextPoint = new Point(0, 0);
        Point LinePoint = new Point(0, 0);
        bool LinePointValid = false;

        private ArduinoPort arduinoport;

        Range DrawInput = new Range(0, 255);
        Range DrawX, DrawY;

        public GraphForm(ArduinoPort port)
        {
            arduinoport = port;
            InitializeComponent();

            DrawX = new Range(0, GraphPictureBox1.Width);
            DrawY = new Range(0, GraphPictureBox1.Height);

            GraphPlot_1 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_2 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_3 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_4 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));
            GraphPlot_5 = new Graph(50, GraphType.Rolling, GraphPictureBox1.ClientRectangle, new Range(0, 255));


            GraphPlot_1.Color = Color.White;
            GraphPlot_2.Color = Color.Yellow;
            GraphPlot_3.Color = Color.Orange;
            GraphPlot_4.Color = Color.Red;
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

            graphButton1.Font = new Font("Microsoft Sans Serif", 8);
            graphButton2.Font = new Font("Microsoft Sans Serif", 8);
            graphButton3.Font = new Font("Microsoft Sans Serif", 8);
            graphButton4.Font = new Font("Microsoft Sans Serif", 8);
            graphButton1.Font = new Font(graphButton1.Font, FontStyle.Regular);
            graphButton2.Font = new Font(graphButton2.Font, FontStyle.Regular);
            graphButton3.Font = new Font(graphButton3.Font, FontStyle.Regular);
            graphButton4.Font = new Font(graphButton4.Font, FontStyle.Regular);
            graphButton1.Text = "";
            graphButton2.Text = "";
            graphButton3.Text = "";
            graphButton4.Text = "";
            graphButton1.ForeColor = Color.Black;
            graphButton2.ForeColor = Color.Black;
            graphButton3.ForeColor = Color.Black;
            graphButton4.ForeColor = Color.Black;
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
            DrawPenSize = 1;
            DrawPixelSize = 1;
            DrawCirclePenSize = 1;
            DrawTextColor = Color.White;
            DrawLineColor = Color.White;
            DrawPointColor = Color.White;
            DrawCircleColor = Color.White;

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
            LinePointValid = false;

            GraphInputPanel_1.Visible = false;
            GraphInputPanel_2.Visible = false;
            GraphInputPanel_3.Visible = false;
            GraphInputPanel_4.Visible = false;
            GraphInputPanel_5.Visible = false;

            GraphInputLabel_1.Text = "";
            GraphInputLabel_2.Text = "";
            GraphInputLabel_3.Text = "";
            GraphInputLabel_4.Text = "";
            GraphInputLabel_5.Text = "";

            GraphInputType_1 = vp_type.vp_int;
            GraphInputType_2 = vp_type.vp_int;
            GraphInputType_3 = vp_type.vp_int;
            GraphInputType_4 = vp_type.vp_int;
            GraphInputType_5 = vp_type.vp_int;

            GraphInputFlag_1 = false;
            GraphInputFlag_2 = false;
            GraphInputFlag_3 = false;
            GraphInputFlag_4 = false;
            GraphInputFlag_5 = false;

            GraphInputEdit_1 = false;
            GraphInputEdit_2 = false;
            GraphInputEdit_3 = false;
            GraphInputEdit_4 = false;
            GraphInputEdit_5 = false;

            MinGraphInput_1 = long.MinValue;
            MinGraphInput_2 = long.MinValue;
            MinGraphInput_3 = long.MinValue;
            MinGraphInput_4 = long.MinValue;
            MinGraphInput_5 = long.MinValue;

            MaxGraphInput_1 = long.MaxValue;
            MaxGraphInput_2 = long.MaxValue;
            MaxGraphInput_3 = long.MaxValue;
            MaxGraphInput_4 = long.MaxValue;
            MaxGraphInput_5 = long.MaxValue;

            MinGraphInputF_1 = float.MinValue;
            MinGraphInputF_2 = float.MinValue;
            MinGraphInputF_3 = float.MinValue;
            MinGraphInputF_4 = float.MinValue;
            MinGraphInputF_5 = float.MinValue;

            MaxGraphInputF_1 = float.MaxValue;
            MaxGraphInputF_2 = float.MaxValue;
            MaxGraphInputF_3 = float.MaxValue;
            MaxGraphInputF_4 = float.MaxValue;
            MaxGraphInputF_5 = float.MaxValue;

            GraphInputText_1 = "";
            GraphInputText_2 = "";
            GraphInputText_3 = "";
            GraphInputText_4 = "";
            GraphInputText_5 = "";

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
                    if ((string)mse.Data == "$CLEAR") { PersistentDrawing.Clear(); LinePointValid = false; }
                }
                if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawCircle && mse.Type == vp_type.vp_string) DrawCircle((string)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawCircle && mse.Type == vp_type.vp_string) SetCirclePen((string)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawLine && mse.Type == vp_type.vp_ulong) DrawPersitentLine((Int64)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawLine && mse.Type == vp_type.vp_string) SetDrawPen((string)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawLine && mse.Type == vp_type.vp_uint) DrawLinePoint((ushort)(int)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawLine && mse.Type == vp_type.vp_void) LinePointValid = false;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawPixel && mse.Type == vp_type.vp_uint) DrawPixel((ushort)(int)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphDrawPixel && mse.Type == vp_type.vp_string) SetDrawPointPen((string)mse.Data); ;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphText && mse.Type == vp_type.vp_uint) DrawTextPos((Int32)mse.Data);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphText && mse.Type == vp_type.vp_string) Drawtext((string)mse.Data);

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

                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_1 && mse.Type == vp_type.vp_byte) { GraphValueAdd((int)mse.Data, GraphPlot_1); } //Grid = true; removed
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_2 && mse.Type == vp_type.vp_byte) { GraphValueAdd((int)mse.Data, GraphPlot_2); }
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_3 && mse.Type == vp_type.vp_byte) { GraphValueAdd((int)mse.Data, GraphPlot_3); }
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_4 && mse.Type == vp_type.vp_byte) { GraphValueAdd((int)mse.Data, GraphPlot_4); }
                if ((ChannelId)mse.ChannelID == ChannelId.GraphValue_5 && mse.Type == vp_type.vp_byte) { GraphValueAdd((int)mse.Data, GraphPlot_5); }

                if ((ChannelId)mse.ChannelID == ChannelId.GraphCaption_1 && mse.Type == vp_type.vp_string) DrawCaption((string)mse.Data, 1);
                if ((ChannelId)mse.ChannelID == ChannelId.GraphCaption_2 && mse.Type == vp_type.vp_string) DrawCaption((string)mse.Data, 2);

                GraphPictureBox1.Invalidate();

                if ((ChannelId)mse.ChannelID == ChannelId.GraphInput_1 && mse.Type == vp_type.vp_boolean) GraphInputFlag_1 = (bool)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphInput_2 && mse.Type == vp_type.vp_boolean) GraphInputFlag_2 = (bool)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphInput_3 && mse.Type == vp_type.vp_boolean) GraphInputFlag_3 = (bool)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphInput_4 && mse.Type == vp_type.vp_boolean) GraphInputFlag_4 = (bool)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.GraphInput_5 && mse.Type == vp_type.vp_boolean) GraphInputFlag_5 = (bool)mse.Data;

                if ((ChannelId)mse.ChannelID == ChannelId.GraphInputLabel_1 && mse.Type == vp_type.vp_string) GraphInputLabel_1.Text = mse.Data.ToString();
                if ((ChannelId)mse.ChannelID == ChannelId.GraphInputLabel_2 && mse.Type == vp_type.vp_string) GraphInputLabel_2.Text = mse.Data.ToString();
                if ((ChannelId)mse.ChannelID == ChannelId.GraphInputLabel_3 && mse.Type == vp_type.vp_string) GraphInputLabel_3.Text = mse.Data.ToString();
                if ((ChannelId)mse.ChannelID == ChannelId.GraphInputLabel_4 && mse.Type == vp_type.vp_string) GraphInputLabel_4.Text = mse.Data.ToString();
                if ((ChannelId)mse.ChannelID == ChannelId.GraphInputLabel_5 && mse.Type == vp_type.vp_string) GraphInputLabel_5.Text = mse.Data.ToString();

                if ((ChannelId)mse.ChannelID == ChannelId.MinGraphInput_1 && mse.Type == vp_type.vp_int) MinGraphInput_1 = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinGraphInput_2 && mse.Type == vp_type.vp_int) MinGraphInput_2 = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinGraphInput_3 && mse.Type == vp_type.vp_int) MinGraphInput_3 = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinGraphInput_4 && mse.Type == vp_type.vp_int) MinGraphInput_4 = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinGraphInput_5 && mse.Type == vp_type.vp_int) MinGraphInput_5 = (int)mse.Data;

                if ((ChannelId)mse.ChannelID == ChannelId.MaxGraphInput_1 && mse.Type == vp_type.vp_int) MaxGraphInput_1 = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxGraphInput_2 && mse.Type == vp_type.vp_int) MaxGraphInput_2 = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxGraphInput_3 && mse.Type == vp_type.vp_int) MaxGraphInput_3 = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxGraphInput_4 && mse.Type == vp_type.vp_int) MaxGraphInput_4 = (int)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxGraphInput_5 && mse.Type == vp_type.vp_int) MaxGraphInput_5 = (int)mse.Data;

                if ((ChannelId)mse.ChannelID == ChannelId.MinGraphInput_1 && mse.Type == vp_type.vp_float) MinGraphInputF_1 = (float)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinGraphInput_2 && mse.Type == vp_type.vp_float) MinGraphInputF_2 = (float)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinGraphInput_3 && mse.Type == vp_type.vp_float) MinGraphInputF_3 = (float)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinGraphInput_4 && mse.Type == vp_type.vp_float) MinGraphInputF_4 = (float)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MinGraphInput_5 && mse.Type == vp_type.vp_float) MinGraphInputF_5 = (float)mse.Data;

                if ((ChannelId)mse.ChannelID == ChannelId.MaxGraphInput_1 && mse.Type == vp_type.vp_float) MaxGraphInputF_1 = (float)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxGraphInput_2 && mse.Type == vp_type.vp_float) MaxGraphInputF_2 = (float)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxGraphInput_3 && mse.Type == vp_type.vp_float) MaxGraphInputF_3 = (float)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxGraphInput_4 && mse.Type == vp_type.vp_float) MaxGraphInputF_4 = (float)mse.Data;
                if ((ChannelId)mse.ChannelID == ChannelId.MaxGraphInput_5 && mse.Type == vp_type.vp_float) MaxGraphInputF_5 = (float)mse.Data;

                if ((ChannelId)mse.ChannelID == ChannelId.GraphInput_1)
                {
                    if (mse.Type != vp_type.vp_void && mse.Type != vp_type.vp_boolean)
                    {
                        GraphInputType_1 = mse.Type;
                        GraphInputPanel_1.Visible = true;
                        GraphInputText_1 = mse.Data.ToString();
                        GraphInputTextBox_1.Text = GraphInputText_1;
                    }
                }
                else if ((ChannelId)mse.ChannelID == ChannelId.GraphInput_2)
                {
                    if (mse.Type != vp_type.vp_void && mse.Type != vp_type.vp_boolean)
                    {
                        GraphInputType_2 = mse.Type;
                        GraphInputPanel_2.Visible = true;
                        GraphInputText_2 = mse.Data.ToString();
                        GraphInputTextBox_2.Text = GraphInputText_2;
                    }
                }
                else if ((ChannelId)mse.ChannelID == ChannelId.GraphInput_3)
                {
                    if (mse.Type != vp_type.vp_void && mse.Type != vp_type.vp_boolean)
                    {
                        GraphInputType_3 = mse.Type;
                        GraphInputPanel_3.Visible = true;
                        GraphInputText_3 = mse.Data.ToString();
                        GraphInputTextBox_3.Text = GraphInputText_3;
                    }
                }
                else if ((ChannelId)mse.ChannelID == ChannelId.GraphInput_4)
                {
                    if (mse.Type != vp_type.vp_void && mse.Type != vp_type.vp_boolean)
                    {
                        GraphInputType_4 = mse.Type;
                        GraphInputPanel_4.Visible = true;
                        GraphInputText_4 = mse.Data.ToString();
                        GraphInputTextBox_4.Text = GraphInputText_4;
                    }
                }
                else if ((ChannelId)mse.ChannelID == ChannelId.GraphInput_5)
                {
                    if (mse.Type != vp_type.vp_void && mse.Type != vp_type.vp_boolean)
                    {
                        GraphInputType_5 = mse.Type;
                        GraphInputPanel_5.Visible = true;
                        GraphInputText_5 = mse.Data.ToString();
                        GraphInputTextBox_5.Text = GraphInputText_5;
                    }
                }
            }
        }


        private void SetGraphAttr(string data, Graph GraphPlot)
        {
            Color col = VirtualPanelForm.String2Color(data);
            if (!col.IsEmpty)
                GraphPlot.Color = col; //
            else
            {

                if (data == "$CLEAR") GraphPlot.ClearData();
                if (data == "$ROLLING") GraphPlot.Type = GraphType.Rolling;
                if (data == "$STATIC") GraphPlot.Type = GraphType.Static;
                if (data == "$1PX") GraphPlot.PlotWidth = 1;
                if (data == "$2PX") GraphPlot.PlotWidth = 2;
                if (data == "$3PX") GraphPlot.PlotWidth = 3;
                if (data == "$4PX") GraphPlot.PlotWidth = 4;
            }
        }

        private void Drawtext(string data)
        {
            Color col = VirtualPanelForm.String2Color(data);
            if (!col.IsEmpty)
                DrawTextColor = col; //
            else
            {
                if(DrawTextColor == Color.Black)
                  PersistentDrawing.Delete(new Text(DrawtextPoint, data, DrawTextColor, 8));
                else
                  PersistentDrawing.Add(new Text(DrawtextPoint, data, DrawTextColor, 8));
                GraphPictureBox1.Invalidate();
            }
        }

        private void DrawCaption(string data, int CaptionId)
        {
            if (DrawTextColor == Color.Black)
            {
                if (CaptionId == 1) PersistentDrawing.Delete(new Text(new Point(10, 5), data, DrawTextColor, 8));
                if (CaptionId == 2) PersistentDrawing.Delete(new Text(new Point(10, 202), data, DrawTextColor, 8));
            }
            else
            {
                if (CaptionId == 1) PersistentDrawing.Add(new Text(new Point(10, 5), data, DrawTextColor, 8));
                if (CaptionId == 2) PersistentDrawing.Add(new Text(new Point(10, 202), data, DrawTextColor, 8));
            }
            GraphPictureBox1.Invalidate();
        }

        private void DrawTextPos(int data)
        {
            string hexdata = "";
            int x = 0;
            int y = 0;
            hexdata = Convert.ToUInt16(data).ToString("X4");
            x = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(0, 2), 16))) + 4;
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
            xs = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(0, 2), 16))) + 4;
            ys = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(2, 2), 16)));
            xe = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(4, 2), 16))) + 4;
            ye = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(hexdata.Substring(6, 2), 16)));
            ys = GraphPictureBox1.Height - ys;
            ye = GraphPictureBox1.Height - ye;

            if (DrawLineColor == Color.Black)
                PersistentDrawing.Delete(new Line(xs, ys, xe, ye, DrawLineColor, DrawPenSize));
            else
            PersistentDrawing.Add(new Line(xs, ys, xe, ye, DrawLineColor, DrawPenSize));
            GraphPictureBox1.Invalidate();
        }


        private void DrawCircle(String CircleParams)
        {
            int xc = 0;
            int yc = 0;
            int radius = 0;
            int startAngle = 0;
            int arcAngle = 0;

            if(CircleParams.Substring(0, 2) == "$$") // hexcoded circle parameters? (byte x)(byte y)(byte radius)(int startangle)(int arc)
            {
                xc = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(CircleParams.Substring(2, 2), 16)));
                yc = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(CircleParams.Substring(4, 2), 16)));
                radius = Convert.ToInt32(Convert.ToByte(Convert.ToInt16(CircleParams.Substring(6, 2), 16)));
                startAngle = Convert.ToInt32(Convert.ToInt16(CircleParams.Substring(8, 4), 16));
                arcAngle = Convert.ToInt32(Convert.ToInt16(CircleParams.Substring(12, 4), 16));
                xc = xc + 4; // within draw box
                yc = GraphPictureBox1.Height - yc; // botom to top
                startAngle = startAngle - 90;
                radius = radius * 2; // radius to box size

                if (DrawLineColor == Color.Black || radius == 0)
                    PersistentDrawing.Delete(new Circle(xc, yc, DrawCircleColor, radius, DrawCirclePenSize, startAngle, arcAngle));
                else
                    PersistentDrawing.Add(new Circle(xc, yc, DrawCircleColor, radius, DrawCirclePenSize, startAngle, arcAngle));
                GraphPictureBox1.Invalidate();
            }
        }


        private void DrawLinePoint(ushort data)
        {
            Point DrawPoint = ExtentionMethodss.FromUInt(data);

            DrawPoint.X = DrawPoint.X + 4;
            DrawPoint.Y = GraphPictureBox1.Height - DrawPoint.Y;

            //DrawPoint.X = (int)((float)DrawPoint.X).Map(DrawInput, DrawX);
            //DrawPoint.Y = (int)((float)DrawPoint.Y).Map(DrawInput, DrawY);

            if (LinePointValid)
            {
                if (DrawLineColor == Color.Black)
                    PersistentDrawing.Delete(new Line(LinePoint, DrawPoint, DrawLineColor, DrawPenSize));
                else
                    PersistentDrawing.Add(new Line(LinePoint, DrawPoint, DrawLineColor, DrawPenSize));

                GraphPictureBox1.Invalidate();
                LinePoint = DrawPoint;
            }
            else
            {
                LinePoint = DrawPoint;
                LinePointValid = true;
            }
        }

        private void DrawPixel(ushort data)
        {
            Point DrawPoint = ExtentionMethodss.FromUInt(data);

            DrawPoint.X = DrawPoint.X + 4;
            DrawPoint.Y = GraphPictureBox1.Height - DrawPoint.Y;

            if (DrawLineColor == Color.Black)
                PersistentDrawing.Delete(new Pixel(DrawPoint.X, DrawPoint.Y, DrawPointColor, DrawPixelSize));
            else
                PersistentDrawing.Add(new Pixel(DrawPoint.X, DrawPoint.Y, DrawPointColor, DrawPixelSize));

            GraphPictureBox1.Invalidate();
        }

        private void SetDrawPointPen(string PenColor)
        {
            Color col = VirtualPanelForm.String2Color(PenColor);
            if (!col.IsEmpty) DrawPointColor = col; //
            if (PenColor == "$1PX") DrawPixelSize = 1;
            if (PenColor == "$2PX") DrawPixelSize = 2;
            if (PenColor == "$3PX") DrawPixelSize = 3;
            if (PenColor == "$4PX") DrawPixelSize = 4;
        }

        private void SetDrawPen(string PenColor)
        {
            Color col = VirtualPanelForm.String2Color(PenColor);
            if (!col.IsEmpty) DrawLineColor = col; //
            if (PenColor == "$1PX") DrawPenSize = 1;
            if (PenColor == "$2PX") DrawPenSize = 2;
            if (PenColor == "$3PX") DrawPenSize = 3;
            if (PenColor == "$4PX") DrawPenSize = 4;
        }

        private void SetCirclePen(string PenColor)
        {
            Color col = VirtualPanelForm.String2Color(PenColor);
            if (!col.IsEmpty) DrawCircleColor = col; //
            if (PenColor == "$1PX") DrawCirclePenSize = 1;
            if (PenColor == "$2PX") DrawCirclePenSize = 2;
            if (PenColor == "$3PX") DrawCirclePenSize = 3;
            if (PenColor == "$4PX") DrawCirclePenSize = 4;
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
                if (!(bool)mse.Data)
                {
                    control.Visible = false;
                    p.Visible = false;
                }
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
                if (GridCount <= 0) GridCount = 0;
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
            }
        }

        private void GraphPictureBox1_Click(object sender, MouseEventArgs e)
        {
            if ((e.Location.X - 4) >= 0 && (e.Location.X - 4) <= 255)
            {
                int pos = ((e.Location.X - 4) * 256) + (GraphPictureBox1.Height - e.Location.Y);

                if (e.Button == MouseButtons.Left)
                {
                    if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphClick, vp_type.vp_uint, pos);
                }
                else if (e.Button == MouseButtons.Right)
                {
                    if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphRightClick, vp_type.vp_uint, pos);
                }
            }

        }


        private void GraphPictureBox1_DoubleClick(object sender, MouseEventArgs e)
        {
            if ((e.Location.X - 4) >= 0 && (e.Location.X - 4) <= 255)
            {
                int pos = (e.Location.X * 256) + (GraphPictureBox1.Height - e.Location.Y);
                if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphDoubleClick, vp_type.vp_uint, pos);
            }
        }

        private void GraphLabelInputRequest(object sender, EventArgs e)
        {
            if (sender == graphLabel1) if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphLabel_1);
            if (sender == graphLabel2) if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphLabel_2);
            if (sender == graphLabel3) if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphLabel_3);
            if (sender == graphLabel4) if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphLabel_4);
            if (sender == graphLabel5) if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphLabel_5);
        }


        private void GraphDiscardInput_Click(object sender, EventArgs e)
        {
            if (sender == GraphDiscardInput_1)
            {
                if (!GraphInputFlag_1) GraphInputPanel_1.Visible = false;
                if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphInput_1);
                GraphInputTextBox_1.Text = GraphInputText_1;
                GraphInputTextBox_1.ForeColor = Color.Black;
            }
            if (sender == GraphDiscardInput_2)
            {
                if (!GraphInputFlag_2) GraphInputPanel_2.Visible = false;
                if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphInput_2);
                GraphInputTextBox_2.Text = GraphInputText_2;
                GraphInputTextBox_2.ForeColor = Color.Black;
            }
            if (sender == GraphDiscardInput_3)
            {
                if (!GraphInputFlag_3) GraphInputPanel_3.Visible = false;
                if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphInput_3);
                GraphInputTextBox_3.Text = GraphInputText_3;
                GraphInputTextBox_3.ForeColor = Color.Black;
            }
            if (sender == GraphDiscardInput_4)
            {
                if (!GraphInputFlag_4) GraphInputPanel_4.Visible = false;
                if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphInput_4);
                GraphInputTextBox_4.Text = GraphInputText_4;
                GraphInputTextBox_4.ForeColor = Color.Black;
            }
            if (sender == GraphDiscardInput_5)
            {
                if (!GraphInputFlag_5) GraphInputPanel_5.Visible = false;
                if (arduinoport.IsConnected) arduinoport.Send((byte)ChannelId.GraphInput_5);
                GraphInputTextBox_5.Text = GraphInputText_5;
                GraphInputTextBox_5.ForeColor = Color.Black;
            }

            AcceptButton = null;
            CancelButton = null;
        }


        private void GraphSendInput_Click(object sender, EventArgs e)
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
            ChannelId GraphInput = ChannelId.GraphInput_1;
            vp_type GraphInputType = vp_type.vp_int;
            bool GraphInputFlag = false;
            bool Valid = true;

            if (sender == GraphSendInput_1)
            {
                Panel = GraphInputPanel_1;
                TextBox = GraphInputTextBox_1;
                GraphInput = ChannelId.GraphInput_1;
                GraphInputType = GraphInputType_1;
                GraphInputFlag = GraphInputFlag_1;
                MinInput = MinGraphInput_1;
                MaxInput = MaxGraphInput_1;
                MinInputF = MinGraphInputF_1;
                MaxInputF = MaxGraphInputF_1;
            }
            if (sender == GraphSendInput_2)
            {
                Panel = GraphInputPanel_2;
                TextBox = GraphInputTextBox_2;
                GraphInput = ChannelId.GraphInput_2;
                GraphInputType = GraphInputType_2;
                GraphInputFlag = GraphInputFlag_2;
                MinInput = MinGraphInput_2;
                MaxInput = MaxGraphInput_2;
                MinInputF = MinGraphInputF_2;
                MaxInputF = MaxGraphInputF_2;
            }
            if (sender == GraphSendInput_3)
            {
                Panel = GraphInputPanel_3;
                TextBox = GraphInputTextBox_3;
                GraphInput = ChannelId.GraphInput_3;
                GraphInputType = GraphInputType_3;
                GraphInputFlag = GraphInputFlag_3;
                MinInput = MinGraphInput_3;
                MaxInput = MaxGraphInput_3;
                MinInputF = MinGraphInputF_3;
                MaxInputF = MaxGraphInputF_3;
            }
            if (sender == GraphSendInput_4)
            {
                Panel = GraphInputPanel_4;
                TextBox = GraphInputTextBox_4;
                GraphInput = ChannelId.GraphInput_4;
                GraphInputType = GraphInputType_4;
                GraphInputFlag = GraphInputFlag_4;
                MinInput = MinGraphInput_4;
                MaxInput = MaxGraphInput_4;
                MinInputF = MinGraphInputF_4;
                MaxInputF = MaxGraphInputF_4;
            }
            if (sender == GraphSendInput_5)
            {
                Panel = GraphInputPanel_5;
                TextBox = GraphInputTextBox_5;
                GraphInput = ChannelId.GraphInput_5;
                GraphInputType = GraphInputType_5;
                GraphInputFlag = GraphInputFlag_5;
                MinInput = MinGraphInput_5;
                MaxInput = MaxGraphInput_5;
                MinInputF = MinGraphInputF_5;
                MaxInputF = MaxGraphInputF_5;
            }


            if (!GraphInputFlag) Panel.Visible = false;
            TextBox.ForeColor = Color.Black;

            if (GraphInputType == vp_type.vp_byte && byte.TryParse(TextBox.Text, out InputValueByte)
                 && (InputValueByte >= MinInput && InputValueByte <= MaxInput))
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)GraphInput, vp_type.vp_byte, InputValueByte);
            }
            else if (GraphInputType == vp_type.vp_int && Int16.TryParse(TextBox.Text, out InputValueShort)
                      && (InputValueShort >= MinInput && InputValueShort <= MaxInput))
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)GraphInput, vp_type.vp_int, InputValueShort);
            }
            else if (GraphInputType == vp_type.vp_uint && UInt16.TryParse(TextBox.Text, out InputValueUShort)
                      && (InputValueUShort >= MinInput && InputValueUShort <= MaxInput))
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)GraphInput, vp_type.vp_uint, InputValueUShort);
            }
            else if (GraphInputType == vp_type.vp_long && Int32.TryParse(TextBox.Text, out InputValueLong)
                      && (InputValueLong >= MinInput && InputValueLong <= MaxInput))
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)GraphInput, vp_type.vp_long, InputValueLong);
            }
            else if (GraphInputType == vp_type.vp_ulong && UInt32.TryParse(TextBox.Text, out InputValueULong)
                      && (InputValueULong >= MinInput && InputValueULong <= MaxInput))
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)GraphInput, vp_type.vp_ulong, InputValueULong);
            }
            else if (GraphInputType == vp_type.vp_float && float.TryParse(TextBox.Text, out InputValueFloat)
                      && (InputValueFloat >= MinInputF && InputValueFloat <= MaxInputF))
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)GraphInput, InputValueFloat);
            }
            else if (GraphInputType == vp_type.vp_string && TextBox.Text.Length <= 35 && TextBox.Text.Length <= MaxInput && TextBox.Text.Length >= MinInput)
            {
                if (arduinoport.IsConnected) arduinoport.Send((byte)GraphInput, TextBox.Text);
            }
            else
            {
                TextBox.ForeColor = Color.Red;
                Panel.Visible = true;
                Valid = false;
            }

            if (Valid)
            {
                if (sender == GraphSendInput_1) GraphInputText_1 = TextBox.Text;
                if (sender == GraphSendInput_2) GraphInputText_2 = TextBox.Text;
                if (sender == GraphSendInput_3) GraphInputText_3 = TextBox.Text;
                if (sender == GraphSendInput_4) GraphInputText_4 = TextBox.Text;
                if (sender == GraphSendInput_5) GraphInputText_5 = TextBox.Text;
            }

            AcceptButton = null;
            CancelButton = null;
        }


        private void GraphInputTextBox_TextChange(object sender, EventArgs e)
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

            TextBox TextBox = (TextBox)sender;
            vp_type GraphInputType = vp_type.vp_int;

            Color EditColor = Color.Blue;

            if (sender == GraphInputTextBox_1 && !GraphInputEdit_1) { EditColor = Color.Black; GraphInputEdit_1 = true; }
            if (sender == GraphInputTextBox_2 && !GraphInputEdit_2) { EditColor = Color.Black; GraphInputEdit_2 = true; }
            if (sender == GraphInputTextBox_3 && !GraphInputEdit_3) { EditColor = Color.Black; GraphInputEdit_3 = true; }
            if (sender == GraphInputTextBox_4 && !GraphInputEdit_4) { EditColor = Color.Black; GraphInputEdit_4 = true; }
            if (sender == GraphInputTextBox_5 && !GraphInputEdit_5) { EditColor = Color.Black; GraphInputEdit_5 = true; }

            if (sender == GraphInputTextBox_1)
            { GraphInputType = GraphInputType_1; MinInput = MinGraphInput_1; MaxInput = MaxGraphInput_1; MinInputF = MinGraphInputF_1; MaxInputF = MaxGraphInputF_1;
                AcceptButton = GraphSendInput_1; CancelButton = GraphDiscardInput_1;
            }
            if (sender == GraphInputTextBox_2)
            { GraphInputType = GraphInputType_2; MinInput = MinGraphInput_2; MaxInput = MaxGraphInput_2; MinInputF = MinGraphInputF_2; MaxInputF = MaxGraphInputF_2;
                AcceptButton = GraphSendInput_2; CancelButton = GraphDiscardInput_2;
            }
            if (sender == GraphInputTextBox_3)
            { GraphInputType = GraphInputType_3; MinInput = MinGraphInput_3; MaxInput = MaxGraphInput_3; MinInputF = MinGraphInputF_3; MaxInputF = MaxGraphInputF_3;
                AcceptButton = GraphSendInput_3; CancelButton = GraphDiscardInput_3;
            }
            if (sender == GraphInputTextBox_4)
            { GraphInputType = GraphInputType_4; MinInput = MinGraphInput_4; MaxInput = MaxGraphInput_4; MinInputF = MinGraphInputF_4; MaxInputF = MaxGraphInputF_4;
                AcceptButton = GraphSendInput_4; CancelButton = GraphDiscardInput_4;
            }
            if (sender == GraphInputTextBox_5)
            { GraphInputType = GraphInputType_5; MinInput = MinGraphInput_5; MaxInput = MaxGraphInput_5; MinInputF = MinGraphInputF_5; MaxInputF = MaxGraphInputF_5;
              AcceptButton = GraphSendInput_5; CancelButton = GraphDiscardInput_5;
            }

            TextBox.ForeColor = EditColor;

            if (GraphInputType == vp_type.vp_byte && byte.TryParse(TextBox.Text, out InputValueByte))
            {
                if (InputValueByte >= MinInput && InputValueByte <= MaxInput)
                {
                    ValueValid = true;
                }
            }
            else if (GraphInputType == vp_type.vp_int && Int16.TryParse(TextBox.Text, out InputValueShort))
            {
                if (InputValueShort >= MinInput && InputValueShort <= MaxInput)
                {
                    ValueValid = true;
                }
            }
            else if (GraphInputType == vp_type.vp_uint && UInt16.TryParse(TextBox.Text, out InputValueUShort))
            {
                if (InputValueUShort >= MinInput && InputValueUShort <= MaxInput)
                {
                    ValueValid = true;
                }
            }
            else if (GraphInputType == vp_type.vp_long && Int32.TryParse(TextBox.Text, out InputValueLong))
            {
                if (InputValueLong >= MinInput && InputValueLong <= MaxInput)
                {
                    ValueValid = true;
                }
            }
            else if (GraphInputType == vp_type.vp_ulong && UInt32.TryParse(TextBox.Text, out InputValueULong))
            {
                if (InputValueULong >= MinInput && InputValueULong <= MaxInput)
                {
                    ValueValid = true;
                }
            }
            else if (GraphInputType == vp_type.vp_float && float.TryParse(TextBox.Text, out InputValueFloat))
            {
                if (InputValueFloat >= MinInputF && InputValueFloat <= MaxInputF)
                {
                    ValueValid = true;
                }
            }
            else if (GraphInputType == vp_type.vp_string)
            {
                if (TextBox.Text.Length <= 35 && TextBox.Text.Length <= MaxInput && TextBox.Text.Length >= MinInput)
                {
                    ValueValid = true;
                }
            }

            if (!ValueValid) TextBox.ForeColor = Color.Red;
        }

    }
}





