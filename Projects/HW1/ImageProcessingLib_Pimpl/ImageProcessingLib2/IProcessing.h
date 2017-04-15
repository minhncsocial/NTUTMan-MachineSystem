#pragma once

#ifndef		IPROCESSING_H
#define		IPROCESSING_H

#include "stdafx.h"

#define IPROCESSING_API __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif

IPROCESSING_API int __cdecl testAdd(int a, int b);

IPROCESSING_API LONG_PTR __cdecl CreatecmImage();
IPROCESSING_API bool __cdecl DestroycmImage(LONG_PTR _mImage);

IPROCESSING_API bool __cdecl Load(LONG_PTR _Image, const char * filename);
IPROCESSING_API bool __cdecl Save(LONG_PTR _Image, char * filename);

IPROCESSING_API int __cdecl GetWidth(LONG_PTR _Image);
IPROCESSING_API int __cdecl GetHeight(LONG_PTR _Image);

IPROCESSING_API HBITMAP* __cdecl GetBitmap(LONG_PTR _Image);
IPROCESSING_API bool __cdecl aThreshold(LONG_PTR _Image,int n,double ff);

#ifdef __cplusplus
}
#endif

#endif //IPROCESSING_IMPL_H