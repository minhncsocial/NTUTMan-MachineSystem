#ifndef		IMAGEPROCESSDLL_H
#define		IMAGEPROCESSDLL_H

#include "stdafx.h"

//#ifdef DLLLIB01_EXPORTS
#define DLLLIB01_API __declspec(dllexport)
//#else
//#define DLLLIB01_API __declspec(dllimport)
//#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma once
//============================================================================================
// This is an example of an exported function.
DLLLIB01_API int __cdecl testAdd(int a, int b);

//class ImageProcessDLL
//{
//public:
//	ImageProcessDLL(void);
//	~ImageProcessDLL(void);
//};

DLLLIB01_API LONG_PTR __cdecl CreateCImage();
DLLLIB01_API bool __cdecl DestroyCImage(LONG_PTR CImg);
DLLLIB01_API bool __cdecl Load(LONG_PTR CImg, char * filename);
DLLLIB01_API bool __cdecl Save(LONG_PTR CImg, char * filename);
DLLLIB01_API HBITMAP* __cdecl GetBitmap(LONG_PTR CImg);
DLLLIB01_API HBITMAP* __cdecl Threshold(LONG_PTR CImg);

//============================================================================================
#ifdef __cplusplus
}
#endif

#endif