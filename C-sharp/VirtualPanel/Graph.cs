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
            var fromAbs = val - from.Start;
            var fromMaxAbs = from.End - from.Start;

            var normal = fromAbs / fromMaxAbs;

            var toMaxAbs = to.End - to.Start;
            var toAbs = toMaxAbs * normal;

            return toAbs + to.Start;
        }
    }

    public enum RangingType
    {
        Auto,
        Manual
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
            get
            {
                return Math.Abs(End - Start);
            }
        }

        public Range(float start, float end)
        {
            Start = start;
            End = end;
        }
    }

    public class Graph
    {
        private List<float> values = new List<float>();
        private List<float> valueBuffer = new List<float>();

        public int SampleCount { get; set; }
        public GraphType Type { get; set; }
        public RangingType RangingType { get; set; }
        public Range ValueRange { get; set; }

        public Graph()
        {
            
        }

        public Graph(int samplecount, GraphType type, RangingType rangingtype, Range valuerange = default(Range))
        {
            SampleCount = samplecount;
            Type = type;
            RangingType = rangingtype;
            ValueRange = valuerange;
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

            if (RangingType == RangingType.Auto && values.Count >= 2)
                ValueRange = new Range(values.Min(), values.Max());
        }

        public void Draw(Graphics g, Color color, float plotWidth, Rectangle bounds)
        {
            var points = new List<PointF>();

            float xdiff = ((float)bounds.Width - bounds.X) / (SampleCount-1);
            Range yrange = new Range(bounds.Y, bounds.Y + bounds.Height);

            for (int i=0; i < values.Count; i++)
            {
                float x = bounds.X + (i * xdiff);
                float y = values[i].Map(ValueRange, yrange);
                points.Add(new PointF(x, y));
            }

            if (points.Count >= 2)
                g.DrawLines(new Pen(color, plotWidth), points.ToArray());
        }
    }
}
