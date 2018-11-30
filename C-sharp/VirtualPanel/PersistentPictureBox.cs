using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace VirtualPanel
{
    public class PersistentPictureBox : PictureBox
    {
        public Image PersistentImage { get; private set; }
        public Boolean OnPaintPersistent { get; set; } = false;

        public PersistentPictureBox()
        {
            PersistentImage = new Bitmap(Width, Height);
        }

        public Graphics CreatePersistentGraphics()
        {
            return Graphics.FromImage(PersistentImage);
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);

            Image old = PersistentImage;

            PersistentImage = new Bitmap(Width, Height);

            using (Graphics g = Graphics.FromImage(PersistentImage))
            {
                g.DrawImage(old, new Point(0, 0));
            }
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            PaintEventArgs paint = pe;

            pe.Graphics.DrawImage(PersistentImage, new Point(0, 0));

            if (OnPaintPersistent)
                paint = new PaintEventArgs(Graphics.FromImage(PersistentImage), pe.ClipRectangle);
            
            base.OnPaint(paint);
        }
    }
}
