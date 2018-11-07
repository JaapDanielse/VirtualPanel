using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        private Bitmap PictureBoxImage;
        public static Random random = new Random();

        public Form1()
        {
            InitializeComponent();

            PictureBoxImage = new Bitmap(pictureBox1.Width, pictureBox1.Height);

            pictureBox1.Image = PictureBoxImage;

            pictureBox1.BackColor = Color.Black;

        }

        private void button1_Click(object sender, EventArgs e)
        {
            pictureBox1.Invalidate();
            persistentPictureBox1.Invalidate();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            using (Graphics g = Graphics.FromImage(PictureBoxImage))
            {
                pictureBox1.Width = 400;
                Point p1 = new Point(random.Next(0, PictureBoxImage.Width), random.Next(0, PictureBoxImage.Height));
                Point p2 = new Point(random.Next(0, PictureBoxImage.Width), random.Next(0, PictureBoxImage.Height));

                g.DrawLine(new Pen(Color.Red), p1, p2);

                g.FillRectangle(Brushes.Yellow, random.Next(0, PictureBoxImage.Width), random.Next(0, PictureBoxImage.Height), 1, 1);
            }


        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            Point p1 = new Point(random.Next(0, PictureBoxImage.Width), random.Next(0, PictureBoxImage.Height));
            Point p2 = new Point(random.Next(0, PictureBoxImage.Width), random.Next(0, PictureBoxImage.Height));

            e.Graphics.DrawImage(PictureBoxImage, new Point(0, 0));
            e.Graphics.DrawLine(new Pen(Color.Green), p1, p2);
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            Point p1 = new Point(random.Next(0, PictureBoxImage.Width), random.Next(0, PictureBoxImage.Height));
            Point p2 = new Point(random.Next(0, PictureBoxImage.Width), random.Next(0, PictureBoxImage.Height));

            Graphics g = persistentPictureBox1.CreatePersistentGraphics();

            g.DrawImage(PictureBoxImage, new Point(0, 0));
            g.DrawLine(new Pen(Color.Green), p1, p2);
        }

        private void pictureBox1_Resize(object sender, EventArgs e)
        {

        }

        private void persistentPictureBox1_Paint(object sender, PaintEventArgs e)
        {
            Point p1 = new Point(random.Next(0, PictureBoxImage.Width), random.Next(0, PictureBoxImage.Height));
            Point p2 = new Point(random.Next(0, PictureBoxImage.Width), random.Next(0, PictureBoxImage.Height));

            e.Graphics.DrawLine(new Pen(Color.Red), p1, p2);

            e.Graphics.FillRectangle(Brushes.Yellow, random.Next(0, PictureBoxImage.Width), random.Next(0, PictureBoxImage.Height), 1, 1);
        }
    }
}
