using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace MiM_iVision
{
    // Declaring iImage class
    public class iVision
    {
        [DllImport("iVision.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "iGetiMatchVersion")]
        public extern static String iGetiMatchVersion();

        [DllImport("iVision.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "iGetiMatchVersionDate")]
        public extern static String iGetiMatchVersionDate();

        [DllImport("iVision.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "iGetErrorText")]
        public extern static String iGetErrorText(E_iVision_ERRORS eError);

        [DllImport("iVision.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "iGetKeySerial")]
        public extern static E_iVision_ERRORS iGetKeySerial(ref int Serial);
    }
}