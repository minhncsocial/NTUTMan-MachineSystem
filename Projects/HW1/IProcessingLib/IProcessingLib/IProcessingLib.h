//#ifdef DLLLIB01_EXPORTS
#define IPROCESSINGLIB_API __declspec(dllexport)
//#else
//#define IPROCESSINGLIB_API __declspec(dllimport)
//#endif

#include "stdafx.h"

#ifdef __cplusplus
extern "C" {
#endif

IPROCESSINGLIB_API int __cdecl testAdd(int a, int b);

#pragma once
class IProcessingLib
{
public:
	IProcessingLib(void);
	~IProcessingLib(void);
};

IPROCESSINGLIB_API LONG_PTR __cdecl CreateCImage();
IPROCESSINGLIB_API bool __cdecl DestroyCImage(LONG_PTR CImg);
IPROCESSINGLIB_API bool __cdecl Load(LONG_PTR CImg, const char * filename);
IPROCESSINGLIB_API bool __cdecl Save(LONG_PTR CImg, char * filename);
IPROCESSINGLIB_API HBITMAP* __cdecl GetBitmap(LONG_PTR CImg);
IPROCESSINGLIB_API bool __cdecl aThreshold(LONG_PTR CImg,int n,double ff);

#ifdef __cplusplus
}
#endif