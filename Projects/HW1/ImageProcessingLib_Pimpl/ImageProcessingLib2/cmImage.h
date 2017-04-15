#pragma once

#ifndef		MIMAGE_H
#define		MIMAGE_H

#include "stdafx.h"

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

class cmImage
{
public:
	explicit cmImage(void);
	~cmImage(void);

	BOOL		Load(const char * filename);
	BOOL		Save(const char * filename);

	int			GetWidth();
	int			GetHeight();

	HBITMAP*	GetBitmap();

	class		Impl;

private:
	cmImage(const cmImage &);
	const cmImage &operator = (const cmImage &);
	Impl * mImpl;
};


#endif //MIMAGE_H
