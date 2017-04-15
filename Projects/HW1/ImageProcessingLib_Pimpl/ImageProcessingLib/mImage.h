#pragma once

#ifndef		MIMAGE_H
#define		MIMAGE_H

#include "stdafx.h"

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

class mImage
{
public:
	explicit mImage(void);
	~mImage(void);

	void  Create(int _width,int _height,int _bits,DWORD _dwFlags=0);
 	BOOL  IsNull();
	void  Destroy();

	int   GetWidth();
	int   GetHeight();
	int   GetBPP();
	
	void  GetColorTable(int m, int n, RGBQUAD* ColorTab);
	void  SetColorTable(int m, int n, RGBQUAD* ColorTab);
	BYTE* GetPixelAddress(int x,int y);
	COLORREF GetPixel(int x,int y );

	int	  GetPitch();
	int	  GetMaxColorTableEntries();

	BOOL  LoadBMP(LPCSTR filename);
	BOOL  SaveBMP(LPCSTR filename);

	BOOL  Load(const char * filename);
	BOOL  Save(const char * filename);

	HBITMAP* GetBitmap();

	class Impl;

private:
	mImage(const mImage &);
	const mImage &operator = (const mImage &);
	Impl * mImpl;
};

#endif //MIMAGE_H