using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Runtime.InteropServices;

namespace testApp01
{
    public partial class Form1 : Form
    {
        [DllImport("E:\\PROGRAMS\\NTUT_Man Machine System\\Projects\\HW1\\thirdTest\\testDllLib01\\Debug\\testDllLib01.dll", CallingConvention = CallingConvention.Cdecl)]
        static public extern IntPtr CreateClass01();
        [DllImport("E:\\PROGRAMS\\NTUT_Man Machine System\\Projects\\HW1\\thirdTest\\testDllLib01\\Debug\\testDllLib01.dll", CallingConvention = CallingConvention.Cdecl)]
        static public extern void DisposeClass01(IntPtr pClassNameObject);
        [DllImport("E:\\PROGRAMS\\NTUT_Man Machine System\\Projects\\HW1\\thirdTest\\testDllLib01\\Debug\\testDllLib01.dll", CallingConvention = CallingConvention.Cdecl)]
        static public extern IntPtr showNotify(IntPtr pClassNameObject);
        [DllImport("E:\\PROGRAMS\\NTUT_Man Machine System\\Projects\\HW1\\thirdTest\\testDllLib01\\Debug\\testDllLib01.dll", CallingConvention = CallingConvention.Cdecl)]
        static public extern double sum(IntPtr pClassNameObject, double a, double b);
        [DllImport("E:\\PROGRAMS\\NTUT_Man Machine System\\Projects\\HW1\\thirdTest\\testDllLib01\\Debug\\testDllLib01.dll", CallingConvention = CallingConvention.Cdecl)]
        static public extern double testAdd(double a, double b);


        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            double varX = 10; double varY = 20;
            double varT = testAdd(varX, varY);
            textBox1.Text = varT.ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            IntPtr pClassName = CreateClass01();

            //showNotify(pClassName);
            double varX = 20; double varY = 20;
            double varT = sum(pClassName, varX, varY);
            textBox1.Text = varT.ToString();

            DisposeClass01(pClassName);

            pClassName = IntPtr.Zero;
        }
    }
}
