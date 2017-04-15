using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUIforP1
{
    public partial class Form1 : Form
    {
        public IntPtr CImg = P1.CreateCImage();
        public IntPtr hbitmap;
        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "BMP file|*.bmp";
            string path;

            if(openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                path = openFileDialog1.FileName;

                if (P1.LoadBMP(CImg, path))
                {
                    hbitmap = P1.GetBitmap(CImg);

                    if (pictureBox1.Image != null)
                        pictureBox1.Image.Dispose();

                    pictureBox1.Image = System.Drawing.Image.FromHbitmap(hbitmap);
                    pictureBox1.Refresh();
                }
                else
                MessageBox.Show("Error", "Error");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int a = 10;
            int b = 20;
            int c = P1.fnP1(a, b);

            textBox1.Text = c.ToString();
        }
    }
}
