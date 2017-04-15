#pragma once

#ifndef		IPROCESSING_PIMPL_H
#define		IPROCESSING_PIMPL_H

#include "stdafx.h"

#define IPROCESSING_PIMPL_API __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif


IPROCESSING_PIMPL_API int __cdecl testAdd(int a, int b);

IPROCESSING_PIMPL_API LONG_PTR __cdecl CreatemImage();
IPROCESSING_PIMPL_API bool __cdecl DestroyCImage(LONG_PTR _mImage);
IPROCESSING_PIMPL_API bool __cdecl Load(LONG_PTR _mImage, const char * filename);
IPROCESSING_PIMPL_API bool __cdecl Save(LONG_PTR _mImage, char * filename);
IPROCESSING_PIMPL_API int __cdecl GetWidth(LONG_PTR _mImage);
IPROCESSING_PIMPL_API HBITMAP* __cdecl GetBitmap(LONG_PTR _mImage);
IPROCESSING_PIMPL_API bool __cdecl aThreshold(LONG_PTR _mImage,int n,double ff);

#ifdef __cplusplus
}
#endif

#endif //IPROCESSING_IMPL_H