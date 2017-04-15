using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace MiM_iVision
{
    // Declaring iImage class
    public class iImage
    {
        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateGrayiImage")]
        public extern static IntPtr CreateGrayiImage();

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateColoriImage")]
        public extern static IntPtr CreateColoriImage();

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateGrayiImageEx")]
        public extern static IntPtr CreateGrayiImageEx(int wid, int hei);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "CreateColoriImageEx")]
        public extern static IntPtr CreateColoriImageEx(int wid, int hei);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "iImageCopy")]
        public extern static E_iVision_ERRORS iImageCopy(IntPtr DestImg, IntPtr SrcImg);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "DestroyiImage")]
        public extern static E_iVision_ERRORS DestroyiImage(IntPtr iImg);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "iImageResize")]
        public extern static E_iVision_ERRORS iImageResize(IntPtr iImg, int width, int height);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetSubiImage")]
        public extern static E_iVision_ERRORS GetSubiImage(IntPtr DesiImg, IntPtr SrciImg, mRect ROI);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetWidth")]
        public extern static int GetWidth(IntPtr iImg);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetHeight")]
        public extern static int GetHeight(IntPtr iImg);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "iImageIsNULL")]
        public extern static E_iVision_ERRORS iImageIsNULL(IntPtr iImg);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "iGetBitmapAddress")]
        public extern static IntPtr iGetBitmapAddress(IntPtr iImg);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "iPointerToiImage")]
        public extern static E_iVision_ERRORS iPointerToiImage(IntPtr iImg, IntPtr DataSrc, int wid, int hei);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "iPointerFromiImage")]
        public extern static E_iVision_ERRORS iPointerFromiImage(IntPtr iImg, ref byte Destdata, int wid, int hei);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, EntryPoint = "GetBufferSize")]
        public extern static UInt32 GetBufferSize(IntPtr iImg);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "iReadImage")]
        public extern static E_iVision_ERRORS iReadImage(IntPtr iImg, string filename);

        [DllImport("iImage.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "iSaveImage")]
        public extern static E_iVision_ERRORS iSaveImage(IntPtr iImg, string filename);
    }
}