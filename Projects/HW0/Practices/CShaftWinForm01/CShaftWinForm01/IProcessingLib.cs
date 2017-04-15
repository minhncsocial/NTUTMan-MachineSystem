using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace CShaftWinForm01
{
    class IProcessingLib
    {
        [DllImport("IProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "testAdd")]
        public extern static int testAdd(int a, int b);

        [DllImport("IProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateCImage")]
        public extern static IntPtr CreateCImage();
        [DllImport("IProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "DestroyCImage")]
        public extern static bool DestroyCImage(IntPtr CImg);
        [DllImport("IProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Load")]
        public extern static bool Load(IntPtr CImg, string filename);
        [DllImport("IProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetBitmap")]
        public extern static IntPtr GetBitmap(IntPtr CImg);

        [DllImport("IProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "aThreshold")]
        public extern static Boolean aThreshold(IntPtr CImg, int n, double ff);
    }
}
