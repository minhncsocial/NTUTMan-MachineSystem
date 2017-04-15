// DLLLib01.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DLLLib01.h"
#include "Image.h"


// This is an example of an exported variable
DLLLIB01_API int nDLLLib01=0;

// This is an example of an exported function.
DLLLIB01_API int __cdecl fnDLLLib01(int a, int b)
{
	return a + b;
}

// This is the constructor of a class that has been exported.
// see DLLLib01.h for the class definition
CDLLLib01::CDLLLib01()
{
	return;
}

DLLLIB01_API LONG_PTR __cdecl CreateCImage()
{
	return (LONG_PTR)(new CImage());
}

//__declspec(dllexport) LONG_PTR __cdecl CreateCImage();
DLLLIB01_API bool __cdecl DestroyCImage(LONG_PTR CImg)
{
	CImage * Img = (CImage*) CImg;

	if (Img != NULL) delete Img;

	return true;
}

DLLLIB01_API bool __cdecl LoadBMP(LONG_PTR CImg, char * filename)
{
	int bFlag = false;
	CImage * Img = (CImage*) CImg;

	if (Img != 0)
	{
		bFlag = Img->LoadBMP(filename);
	}

	if (bFlag)
	{
		return true;
	}
	else
	{
		return false;
	}
}

DLLLIB01_API bool __cdecl SaveBMP(LONG_PTR CImg, char * filename)
{
	int bFlag = false;
	CImage * Img = (CImage*) CImg;

	if (Img != 0)
	{
		bFlag = Img->SaveBMP(filename);
	}

	if (bFlag)
	{
		return true;
	}
	else
	{
		return false;
	}
}

DLLLIB01_API HBITMAP* __cdecl GetBitmap(LONG_PTR CImg)
{
	CImage* Img = (CImage*)CImg;
	return (HBITMAP*)*(Img->GetBitmap());
}

DLLLIB01_API HBITMAP* __cdecl Threshold(LONG_PTR CImg)
{
	CImage* Img = (CImage*)CImg;

	int _height = Img->GetHeight();
	int _width = Img->GetWidth();

	for (int i = 0; i <= _width; i++)
	{
		for (int j = 0; j <= _height; j++)
		{
			long value = Img->GetPixel(i, j);

		}
	}

	return NULL;
}