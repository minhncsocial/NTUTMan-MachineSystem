#ifndef		IMAGEPROCESSDLL_H
#define		IMAGEPROCESSDLL_H

#include "stdafx.h"

#ifdef DLLLIB01_EXPORTS
#define DLLLIB01_API __declspec(dllexport)
#else
#define DLLLIB01_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//============================================================================================
#pragma once
class IProcessing
{
public:
	IProcessing(void);
	~IProcessing(void);
};

//============================================================================================
#ifdef __cplusplus
}
#endif

#endif