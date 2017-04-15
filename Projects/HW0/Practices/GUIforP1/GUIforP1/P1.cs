using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace GUIforP1
{
    public class P1
    {
        [DllImport("P1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "fnP1")]
        public extern static int fnP1(int a, int b);

        [DllImport("P1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateCImage")]
        public extern static IntPtr CreateCImage();

        [DllImport("P1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "DestroyCImage")]
        public extern static bool DestroyCImage(IntPtr CImg);

        [DllImport("P1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "LoadBMP")]
        public extern static bool LoadBMP(IntPtr CImg, string filename);

        [DllImport("P1.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetBitmap")]
        public extern static IntPtr GetBitmap(IntPtr CImg);
    }
}
