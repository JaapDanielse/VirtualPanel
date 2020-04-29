using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace VirtualPanel
{
    public interface IDrawable
    {
        void Draw(Graphics g);
    }

    public struct Text : IDrawable
    {
        public Point Location { get; set; }
        public String TextLine { get; set; }
        public Color Color { get; set; }
        public float Width { get; set; }

        public Text(int x, int y, string s, Color color, float width)
        {
            Location = new Point(x, y);
            TextLine = s;
            Color = color;
            Width = width;
        }
        public Text(Point loc, string s, Color color, float width)
        {
            Location = loc;
            TextLine = s;
            Color = color;
            Width = width;
        }

        public override bool Equals(Object obj)
        {
            return obj is Text && this == (Text)obj;
        }
        public override int GetHashCode()
        {
            return Location.GetHashCode();
        }
        public static bool operator ==(Text x, Text y)
        {
            return x.Location == y.Location;
        }
        public static bool operator !=(Text x, Text y)
        {
            return !(x == y);
        }

        public void Draw(Graphics g)
        {
            g.DrawString(TextLine, new Font("Verdana", Width), new SolidBrush(Color), Location);
        }
    }

    public struct Line : IDrawable
    {
        public Point Start { get; set; }
        public Point End { get; set; }
        public Color Color { get; set; }
        public float Width { get; set; }

        public Line(int x1, int y1, int x2, int y2, Color color, float width)
        {
            Start = new Point(x1, y1);
            End = new Point(x2, y2);
            Color = color;
            Width = width;
        }
        public Line(Point start, Point end, Color color, float width)
        {
            Start = start;
            End = end;
            Color = color;
            Width = width;
        }

        public override bool Equals(Object obj)
        {
            return obj is Line && this == (Line)obj;
        }
        public override int GetHashCode()
        {
            return Start.GetHashCode() ^ End.GetHashCode();
        }
        public static bool operator ==(Line x, Line y)
        {
            return x.Start == y.Start && x.End == y.End;
        }
        public static bool operator !=(Line x, Line y)
        {
            return !(x == y);
        }
        
        public void Draw(Graphics g)
        {
            g.DrawLine(new Pen(Color, Width), Start, End);
        }
    }

    public struct Pixel : IDrawable
    {
        public Point Location { get; set; }
        public Color Color { get; set; }
        public float Width { get; set; }

        public Pixel(int x, int y, Color color, float width)
        {
            Location = new Point(x, y);
            Color = color;
            Width = width;
        }
        public Pixel(Point loc, Color color, float width)
        {
            Location = loc;
            Color = color;
            Width = width;
        }

        public override bool Equals(Object obj)
        {
            return obj is Pixel && this == (Pixel)obj;
        }
        public override int GetHashCode()
        {
            return Location.GetHashCode();
        }
        public static bool operator ==(Pixel x, Pixel y)
        {
            return x.Location == y.Location;
        }
        public static bool operator !=(Pixel x, Pixel y)
        {
            return !(x == y);
        }

        public void Draw(Graphics g)
        {
            g.FillRectangle(new SolidBrush(Color), Location.X-(Width/2), Location.Y-(Width/2), Width, Width);
        }
    }

    public struct Circle : IDrawable
    {
        public Point Location { get; set; }
        public Color Color { get; set; }
        public float Size { get; set; }
        public float Width { get; set; }
        public Int32 StartAngle { get; set; }
        public Int32 ArcAngle { get; set; }

        public Circle(int x, int y, Color color, float size, float width, int startAngle, int arcAngle)
        {
            Location = new Point(x, y);
            Color = color;
            Size = size;
            Width = width;
            StartAngle = startAngle;
            ArcAngle = arcAngle;
        }
        public Circle(Point loc, Color color, float size, float width, int startAngle, int arcAngle)
        {
            Location = loc;
            Color = color;
            Size = size;
            Width = width;
            StartAngle = startAngle;
            ArcAngle = arcAngle;
        }

        public override bool Equals(Object obj)
        {
            return obj is Circle && this == (Circle)obj;
        }
        public override int GetHashCode()
        {
            return Location.GetHashCode();
        }
        public static bool operator ==(Circle x, Circle y)
        {
            return x.Location == y.Location && x.Size == y.Size && x.StartAngle == y.StartAngle;
        }
        public static bool operator !=(Circle x, Circle y)
        {
            return !(x == y);
        }

        public void Draw(Graphics g)
        {
            g.DrawArc(new Pen(Color, Width), Location.X - (Size / 2), Location.Y - (Size / 2), Size, Size, StartAngle, ArcAngle);
        }
    }

    public class Imagic : IDrawable
    {
        private List<IDrawable> drawables = new List<IDrawable>();

        public void Add(IDrawable drawable)
        { 
            drawables.Remove(drawable);
            drawables.Add(drawable);
        }

        public void Delete(IDrawable drawable)
        {
            drawables.Remove(drawable);
        }

        public void Clear()
        {
            drawables.Clear();
        }

        public void Draw(Graphics g)
        {
            foreach (IDrawable drawable in drawables)
                drawable.Draw(g);
        }

    }
}
