#ifndef		_CIMAGE_H
#define		_CIMAGE_H

#include "stdafx.h"
#include <stdio.h>
#include "stdlib.h"

#pragma once

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

class mImage
{
public:
	mImage(void);
	~mImage(void);

	void  Create(int Width,int Height,int Bits,DWORD dwFlags=0);

	void  SetColorTable(int m, int n, RGBQUAD* ColorTab);

	BOOL  LoadBMP(char* filename);

	HBITMAP* GetBitmap();

private:
	HBITMAP hBitmap;
	LPBYTE lpBits;

	int				nWidth;
	int				nHeight;
	int				nBitCount;
    int				nBytesPerLine;
	int				nBytesPerPixel;
	int				nNumColors;
	int				nSize;

	HDC				hMemDC;
};

#endif