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

namespace MyApp
{
    public partial class Form1 : Form
    {
        [DllImport("MyDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "fnMyDLL")]
        public extern static int fnMyDLL(int a, int b);

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int a = 10;
            int b = 20;
            //int c = MyDLL.fnMyDLL(a, b);
            //int c = MyDLL.fnMyDLL(a, b);
            int c = fnMyDLL(a, b);

            textBox1.Text = c.ToString();
        }
    }
}
