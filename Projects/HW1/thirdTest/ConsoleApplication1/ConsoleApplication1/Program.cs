using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Runtime.InteropServices;

namespace ConsoleApplication1
{
    class Program
    {
        [DllImport("E:\\PROGRAMS\\NTUT_Man Machine System\\Projects\\HW1\\thirdTest\\CppClassDll\\Debug\\CppClassDll.dll")]
        public static extern double sumTwo(double var_x, double var_y);

        static void Main(string[] args)
        {
            double var_x = 10;
            double var_y = 20;

            double result = sumTwo(var_x, var_y);
        }
    }
}
