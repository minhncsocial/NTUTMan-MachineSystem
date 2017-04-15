#include "StdAfx.h"
#include "ImageProcessDLL.h"


//ImageProcessDLL::ImageProcessDLL(void)
//{
//}
//
//
//ImageProcessDLL::~ImageProcessDLL(void)
//{
//}

DLLLIB01_API LONG_PTR __cdecl CreateCImage()
{
	return (LONG_PTR)(new CImage());
}

DLLLIB01_API bool __cdecl DestroyCImage(LONG_PTR CImg)
{
	CImage * Img = (CImage*) CImg;

	if (Img != NULL) delete Img;

	return true;
}

DLLLIB01_API bool __cdecl Load(LONG_PTR CImg, char * filename)
{
	int _flag = false;
	CImage * Img = (CImage*) CImg;
	CString filenameCS(filename);

	std::cout << "Load(LONG_PTR CImg, CString filename)" << " | " << filename << " | " << filenameCS.GetString() << std::endl;

	if (Img != 0)
	{
		_flag = Img->Load((CString)filename);
	}

	if (_flag)
	{
		return true;
	}
	else
	{
		return false;
	}
}

DLLLIB01_API bool __cdecl Save(LONG_PTR CImg, char * filename)
{
	int bFlag = false;
	CImage * Img = (CImage*) CImg;

	if (Img != 0)
	{
		bFlag = Img->Save((CString)filename);
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
