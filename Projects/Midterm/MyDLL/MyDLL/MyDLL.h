#pragma once

#ifndef		MYDLL_H
#define		MYDLL_H

#include "stdafx.h"

#define MYDLL_API __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif

MYDLL_API int __cdecl fnMyDLL(int a, int b);

MYDLL_API LONG_PTR __cdecl CreateCImage();
MYDLL_API bool __cdecl DestroyCImage(LONG_PTR _mImage);

MYDLL_API bool __cdecl LoadBMP(LONG_PTR _Image, const char * filename);
MYDLL_API bool __cdecl Save(LONG_PTR _Image, char * filename);

MYDLL_API int __cdecl GetWidth(LONG_PTR _Image);
MYDLL_API int __cdecl GetHeight(LONG_PTR _Image);

MYDLL_API HBITMAP* __cdecl GetBitmap(LONG_PTR _Image);
MYDLL_API BOOL __cdecl DoBitBlt(LONG_PTR _Image, LONG_PTR hDC);

MYDLL_API void __cdecl ColorToGray(LONG_PTR destImage, LONG_PTR srcImage);
MYDLL_API bool __cdecl aThreshold(LONG_PTR _Image,int n,double ff);

#ifdef __cplusplus
}
#endif

#endif //IPROCESSING_IMPL_H