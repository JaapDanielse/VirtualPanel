using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace VirtualPanel
{
    public class MenuRenderer : ToolStripProfessionalRenderer
    {
        public MenuRenderer() : base(new MyColors()) { }
    }

    public class MyColors : ProfessionalColorTable
    {
        public override Color MenuItemSelectedGradientBegin
        {
            get { return Color.LightGray; }
        }
        public override Color MenuItemSelectedGradientEnd
        {
            get { return Color.LightGray; }
        }
        public override Color MenuItemPressedGradientBegin
        {
            get { return Color.LightGray; }
        }
        public override Color MenuItemPressedGradientEnd
        {
            get { return Color.LightGray; }
        }
        public override Color MenuItemSelected
        {
            get { return Color.LightGray; }
        }
        public override Color MenuItemBorder
        {
            get { return Color.LightGray; }
        }
        public override Color MenuBorder
        {
            get { return Color.LightGray; }
        }
    }
}
