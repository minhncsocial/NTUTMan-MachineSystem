#ifndef CMIMAGE_H
#define CMIMAGE_H

#include "stdafx.h"
#include <stdio.h>
#include "stdlib.h"

#pragma once

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

class cmImage
{
public:
	cmImage(void);
	~cmImage(void);

	void Create(int _width, int _height, int _bits, DWORD _dwFlags = 0);
	BOOL IsNull();
	void Destroy();

	BOOL LoadBMP(char * filename);

private:
	HBITMAP hBitmap;
	LPBYTE    		lpBits;

	int mWidth;
	int mHeight;
	int mBitCount;
	int mBytesPerLine;
	int mBytesPerPixel;
	int mNumColors;
	int mSize;

	HDC hMemDC;
};

#endif // CMIMAGE_H