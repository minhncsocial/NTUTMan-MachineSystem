using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace CShaftWinForm01
{
    class MyDLL
    {
        [DllImport("DLLLib01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "fnDLLLib01")]
        public extern static int fnDLLLib01(int a, int b);

        [DllImport("DLLLib01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "CreateCImage")]
        public extern static IntPtr CreateCImage();
        [DllImport("DLLLib01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "DestroyCImage")]
        public extern static bool DestroyCImage(IntPtr CImg);
        [DllImport("DLLLib01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "LoadBMP")]
        public extern static bool LoadBMP(IntPtr CImg, string filename);
        [DllImport("DLLLib01.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "GetBitmap")]
        public extern static IntPtr GetBitmap(IntPtr CImg);
    }
}
