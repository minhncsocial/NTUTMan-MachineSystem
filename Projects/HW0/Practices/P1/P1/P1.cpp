// P1.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "P1.h"
#include "Image.h"


// This is an example of an exported variable
P1_API int nP1=0;

// This is an example of an exported function.
P1_API int fnP1(int a, int b)
{
	return a + b;
}

P1_API LONG_PTR CreateCImage()
{
	//int dx = 10, dy = 10, bits = 8;
	//DWORD flag = 0;

	//CImage* Img = NULL;
	//if (Img != 0)
	//	Img->Create(dx, dy, bits, flag);

	return (LONG_PTR)(new CImage());
}

P1_API bool DestroyCImage(LONG_PTR CImg)
{
	CImage* Img = (CImage*)CImg;
	
	if (Img != NULL) delete Img;

	return true;
}

P1_API bool LoadBMP(LONG_PTR CImg, char* filename)
{
	int bFlag = false;
	
	CImage* Img = (CImage*) CImg;

	if (Img != 0)
		bFlag = Img->LoadBMP(filename);

	if (bFlag)
		return true;
	else
		return false;
}

P1_API HBITMAP* GetBitmap(LONG_PTR CImg)
{
	CImage* Img = (CImage*)CImg;
	return (HBITMAP*)*(Img->GetBitmap());
}

// This is the constructor of a class that has been exported.
// see P1.h for the class definition
/*CP1::CP1()
{
	return;
}*/
