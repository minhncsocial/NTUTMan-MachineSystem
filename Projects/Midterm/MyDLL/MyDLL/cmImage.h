#pragma once

#ifndef		CMIMAGE_H
#define		CMIMAGE_H

#include "stdafx.h"

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

class cmImage
{
public:
	explicit cmImage(void);
	~cmImage(void);

	BOOL		IsNull();

	BOOL		Load(const char * filename);
	BOOL		Save(const char * filename);

	int			GetWidth();
	int			GetHeight();
	int			GetBPP();

	void		Create(int _width, int _height, int _bits, DWORD _dwFlags=0);
	HBITMAP*	GetBitmap();

	HDC			GetDC();
	void		ReleaseDC();
	BOOL		BitBlt(HDC hDestDC,int xDest,int yDest,
                     int nDestWidth,int nDestHeight,
					 int xSrc,int ySrc,DWORD dwROP);

	class		Impl;

private:
	cmImage(const cmImage &);
	const cmImage &operator = (const cmImage &);
	Impl * mImpl;
};


#endif //CMIMAGE_H
