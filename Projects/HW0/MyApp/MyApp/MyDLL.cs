using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Runtime.InteropServices;



namespace MyApp
{
    public class MyDLL
    {
        [DllImport("MyDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "fnMyDLL")]
        //[DllImport("E:\\PROGRAMS\\NTUT_Man Machine System\\Projects\\HW1\\MyDLL\\Debug\\MyDLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "fnMyDLL")]
        public extern static int fnMyDLL(int a, int b);
    }
}
