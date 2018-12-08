using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VirtualPanel
{
    public static class ExtensionMethods
    {
        public static float Map(this float val, Range from, Range to)
        {
            var normal = (val - from.Start) / from.Abs;
            return to.Start + (normal * to.Abs);
        }
    }

    public enum GraphType
    {
        Rolling,
        Static
    }

    public struct Range
    {
        public float Start;
        public float End;

        public float Abs
        {
            get { return End - Start; }
        }

        public Range(float start, float end)
        {
            Start = start;
            End = end;
        }

        #region Equality
        public override bool Equals(Object obj)
        {
            return obj is Range && this == (Range)obj;
        }
        public override int GetHashCode()
        {
            return Start.GetHashCode() ^ End.GetHashCode();
        }
        public static bool operator ==(Range lhs, Range rhs)
        {
            return lhs.Start == rhs.Start && lhs.End == rhs.End;
        }
        public static bool operator !=(Range lhs, Range rhs)
        {
            return !(lhs == rhs);
        }
        #endregion
    }

    public class Graph : IDrawable
    {
        private List<float> values = new List<float>();
        private List<float> valueBuffer = new List<float>();
        private Boolean autoRange = true;
        private Range valueRange;

        public Color Color { get; set; } = Color.White;
        public float PlotWidth { get; set; } = 1.0f;
        public Rectangle DrawingBounds { get; set; }

        public Boolean AutoRange
        {
            get { return autoRange; }
            set 
            {
                autoRange = value;
                // Updates the range it is switched to auto ranging. 
                if (autoRange && values.Count >= 2)
                    ValueRange = new Range(values.Min(), values.Max());
            }
        }

        public Range ValueRange
        {
            get { return valueRange; } 
            set
            {
                if (value.Abs <= 0)
                    throw new ArgumentException("Value range Start larger or equal than End", "valuerange");

                valueRange = value;
                autoRange = false;
            }
        }

        public int SampleCount { get; set; }
        public GraphType Type { get; set; }   

        public Graph()
        {
            
        }

        public Graph(int samplecount, GraphType type, Rectangle drawingBounds, Range valuerange = default(Range))
        {
            if (valuerange != default(Range))
            {
                ValueRange = valuerange;
                autoRange = false;
            }

            if (drawingBounds.Height < 0 && drawingBounds.Width < 0)
                throw new ArgumentException("Drawing bounds have no size.", "drawingBounds");

            DrawingBounds = drawingBounds;
            SampleCount = samplecount;
            Type = type;
        }

        public void ClearData()
        {
            values.Clear();
            valueBuffer.Clear();
        }

        public void AddValue(float value)
        {
            if (Type == GraphType.Rolling)
            {
                if (values.Count == SampleCount)
                    values.RemoveAt(0);

                values.Add(value);
            }

            if (Type == GraphType.Static)
            {
                if (valueBuffer.Count < SampleCount)
                    valueBuffer.Add(value);

                if (valueBuffer.Count == SampleCount)
                {
                    values = valueBuffer;
                    valueBuffer = new List<float>();
                }
            }

            if (autoRange && values.Count >= 2)
                valueRange = new Range(values.Min(), values.Max());
        }

        public void Draw(Graphics g)
        {
            var points = new List<PointF>();

            float xdiff = ((float)DrawingBounds.Width - DrawingBounds.X) / (SampleCount-1);
            Range yrange = new Range(DrawingBounds.Y, DrawingBounds.Y + DrawingBounds.Height);

            for (int i=0; i < values.Count; i++)
            {
                float x = DrawingBounds.X + (i * xdiff);
                float y = values[i].Map(ValueRange, yrange);
                points.Add(new PointF(x, y));
            }

            if (points.Count >= 2 && valueRange.Abs > 0)
                g.DrawLines(new Pen(Color, PlotWidth), points.ToArray());
        }
    }
}
