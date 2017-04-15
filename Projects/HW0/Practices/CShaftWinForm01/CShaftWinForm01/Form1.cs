using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MiM_iVision;
using System.Runtime.InteropServices;

namespace CShaftWinForm01
{
    public partial class Form1 : Form
    {
        //[DllImport("IProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "testAdd")]
        //public extern static int testAdd(int a, int b);

        //[DllImport("IProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateCImage")]
        //public extern static IntPtr CreateCImage();
        //[DllImport("IProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "DestroyCImage")]
        //public extern static bool DestroyCImage(IntPtr CImg);
        //[DllImport("IProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Load")]
        //public extern static bool Load(IntPtr CImg, string filename);
        //[DllImport("IProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetBitmap")]
        //public extern static IntPtr GetBitmap(IntPtr CImg);

        public IntPtr inputImage = iImage.CreateGrayiImage();
        public IntPtr outputImage = iImage.CreateGrayiImage();
        public Int32 inputWidth = 0, inputHeight = 0;
        public Int32 outputHeight = 0, outputWidth = 0;
        public E_iVision_ERRORS error = E_iVision_ERRORS.E_NULL;
        public IntPtr CImg1 = MyDLL.CreateCImage();
        public IntPtr hBitmap1;
        public IntPtr CImg2 = IProcessingLib.CreateCImage();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            iImage.DestroyiImage(inputImage);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int a = 30;
            int b = 50;
            int c = MyDLL.fnDLLLib01(a, b);

            textBox1.Text = c.ToString();

            error = loadImageFromDialog(sender, e, inputImage);

            if (error == E_iVision_ERRORS.E_OK)
            {
                showImage(sender, e, inputImage);
            }
        }

        public E_iVision_ERRORS loadImageFromDialog(object sender, EventArgs e, IntPtr image)
        {
            openFileDialog1.Filter = "BMP|*.bmp|JPG|*.jpg|PNG|*.png|TIF|*.tif";
            string path;

            if (openFileDialog1.ShowDialog() != DialogResult.OK)
            {
                MessageBox.Show(error.ToString(), "Error: No File Selected");
                return error;
            }

            path = openFileDialog1.FileName;
            error = iImage.iReadImage(image, path);
            inputHeight = iImage.GetHeight(image);
            inputWidth = iImage.GetWidth(image);

            if (error != E_iVision_ERRORS.E_OK)
            {
                MessageBox.Show(error.ToString(), "Error: Not Gray Image");
                return error;
            }

            return E_iVision_ERRORS.E_OK;
        }

        public void showImage(object sender, EventArgs e, IntPtr image)
        {
            IntPtr tempImage = iImage.iGetBitmapAddress(image);
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(tempImage);
            pictureBox1.Refresh();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "BMP|*.bmp|JPG|*.jpg|PNG|*.png|TIF|*.tif";
            string path;

            if (openFileDialog1.ShowDialog() != DialogResult.OK)
            {
                MessageBox.Show(error.ToString(), "Error: No File Selected");
                return;
            }

            path = openFileDialog1.FileName;

            if (MyDLL.LoadBMP(CImg1, path))
            {
                hBitmap1 = MyDLL.GetBitmap(CImg1);

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
            int a = 30;
            int b = 50;
            int d = IProcessingLib.testAdd(a, b);
            textBox2.Text = d.ToString();

            openFileDialog1.Filter = "BMP|*.bmp|JPG|*.jpg|PNG|*.png|TIF|*.tif";
            string pathS;

            if (openFileDialog1.ShowDialog() != DialogResult.OK)
            {
                MessageBox.Show(error.ToString(), "Error: No File Selected");
                return;
            }

            pathS = openFileDialog1.FileName;
            char pathC = System.Convert.ToChar(pathS[0]);
            //char* pathC = (char *)pathS.ToCharArray();
            //char* pathC = (char*)(void*)Marshal::StringToHGlobalAnsi(pathS);

            if (IProcessingLib.Load(CImg2, pathS))
            {
                hBitmap1 = IProcessingLib.GetBitmap(CImg2);

                if (pictureBox1.Image != null) pictureBox1.Image.Dispose();
                pictureBox1.Image = System.Drawing.Image.FromHbitmap(hBitmap1);
                pictureBox1.Refresh();
            }
            else
            {
                MessageBox.Show("Error", "Error");
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            IProcessingLib.aThreshold(CImg2, 3, 0);

            hBitmap1 = IProcessingLib.GetBitmap(CImg2);

            if (pictureBox1.Image != null) pictureBox1.Image.Dispose();
            pictureBox1.Image = System.Drawing.Image.FromHbitmap(hBitmap1);
            pictureBox1.Refresh();
        }
    }
}
