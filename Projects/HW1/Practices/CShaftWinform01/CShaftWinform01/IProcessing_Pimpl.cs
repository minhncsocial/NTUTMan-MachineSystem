using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace CShaftWinform01
{
    class IProcessing_Pimpl
    {
        [DllImport("ImageProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "testAdd")]
        public extern static int testAdd(int a, int b);

        [DllImport("ImageProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreatemImage")]
        public extern static IntPtr CreatemImage();
        [DllImport("ImageProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "DestroyCImage")]
        public extern static bool DestroyCImage(IntPtr _mImage);
        [DllImport("ImageProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Load")]
        public extern static bool Load(IntPtr _mImage, string filename);
        [DllImport("ImageProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetBitmap")]
        public extern static IntPtr GetBitmap(IntPtr _mImage);

        [DllImport("ImageProcessingLib.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetWidth")]
        public extern static Int16 GetWidth(IntPtr _mImage);
    }
}
