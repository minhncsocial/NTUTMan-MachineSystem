using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace CShaftWinform01
{
    class IProcessing_Pimpl2
    {
        [DllImport("ImageProcessingLib2.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "testAdd")]
        public extern static int testAdd(int _a, int _b);

        [DllImport("ImageProcessingLib2.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreatecmImage")]
        public extern static IntPtr CreatecmImage();
        [DllImport("ImageProcessingLib2.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "DestroycmImage")]
        public extern static bool DestroycmImage(IntPtr _Image);
        [DllImport("ImageProcessingLib2.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Load")]
        public extern static bool Load(IntPtr _Image, string _filename);
        [DllImport("ImageProcessingLib2.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetBitmap")]
        public extern static IntPtr GetBitmap(IntPtr _Image);

        [DllImport("ImageProcessingLib2.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetWidth")]
        public extern static Int16 GetWidth(IntPtr _Image);
        [DllImport("ImageProcessingLib2.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetHeight")]
        public extern static Int16 GetHeight(IntPtr _Image);
    }
}
