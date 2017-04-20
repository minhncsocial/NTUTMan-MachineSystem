#pragma once

#ifndef		SUBIPROCESS_H
#define		SUBIPROCESS_H

#include	"stdafx.h"

struct IMAGEPARAMENT {       
	int		nWidth;
	int		nHeight;
	int		nBitCount;
    int		nBytesPerLine;
	int		nBytesPerPixel;
	int		nNumColors;
	int		nSize;
};

void GetImageParament(cmImage *pImg, struct IMAGEPARAMENT *ppImgParam);

//=====================================================================

//void ColorToGray(cmImage *pImgn, cmImage *pImgm);
//void Threshold(cmImage *pImgm, int n, double ff);

#endif //SUBIPROCESS_H
