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
        private double testValue = 10;
        //private char* dllDir = "E:\PROGRAMS\NTUT_Man Machine System\Projects\HW1\secondTest\testDynamicLibrary\Debug\MathFuncDll.dll";

        [DllImport("E:\\PROGRAMS\\NTUT_Man Machine System\\Projects\\HW1\\secondTest\\testDynamicLibrary03\\Debug\\MathFuncDll03.dll", CallingConvention = CallingConvention .Cdecl)]
        public static extern double Add(double a, double b);
        [DllImport("E:\\PROGRAMS\\NTUT_Man Machine System\\Projects\\HW1\\secondTest\\testDynamicLibrary03\\Debug\\MathFuncDll03.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double Subtract(double a, double b);
        [DllImport("E:\\PROGRAMS\\NTUT_Man Machine System\\Projects\\HW1\\secondTest\\testDynamicLibrary03\\Debug\\MathFuncDll03.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double Multiply(double a, double b);
        [DllImport("E:\\PROGRAMS\\NTUT_Man Machine System\\Projects\\HW1\\secondTest\\testDynamicLibrary03\\Debug\\MathFuncDll03.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double Divide(double a, double b);
        [DllImport("E:\\PROGRAMS\\NTUT_Man Machine System\\Projects\\HW1\\secondTest\\testDynamicLibrary03\\Debug\\MathFuncDll03.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int fnMathFuncDll03();

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            testValue = Add(testValue, testValue);
            label1.Text = testValue.ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //testValue = Subtract(testValue, testValue);
            testValue = fnMathFuncDll03();
            label1.Text = testValue.ToString();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            testValue = Multiply(testValue, testValue);
            label1.Text = testValue.ToString();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            testValue = Divide(testValue, testValue);
            label1.Text = testValue.ToString();
        }
    }
}

