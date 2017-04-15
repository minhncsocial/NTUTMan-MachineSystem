using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CShaftWinform01
{
    public partial class Form1 : Form
    {
        public IntPtr mImg1 = IProcessing_Pimpl.CreatemImage();
        public IntPtr hBitmap1;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int a = 10;
            int b = 20;
            int c = IProcessing_Pimpl.testAdd(a, b);

            textBox1.Text = c.ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "BMP|*.bmp|JPG|*.jpg|PNG|*.png|TIF|*.tif";
            string pathS;

            if (openFileDialog1.ShowDialog() != DialogResult.OK)
            {
                MessageBox.Show("Error: No File Selected");
                return;
            }

            pathS = openFileDialog1.FileName;
            char pathC = System.Convert.ToChar(pathS[0]);

            if (IProcessing_Pimpl.Load(mImg1, pathS))
            {
                hBitmap1 = IProcessing_Pimpl.GetBitmap(mImg1);

                if (pictureBox1.Image != null) pictureBox1.Image.Dispose();
                pictureBox1.Image = System.Drawing.Image.FromHbitmap(hBitmap1);
                pictureBox1.Refresh();
            }
            else
            {
                MessageBox.Show("Error", "Error");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int width = IProcessing_Pimpl.GetWidth(mImg1);

            textBox2.Text = width.ToString();
        }
    }
}
