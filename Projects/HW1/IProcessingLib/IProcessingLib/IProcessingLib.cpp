#include "IProcessingLib.h"

IPROCESSINGLIB_API int __cdecl testAdd(int a, int b)
{
	return (a + b);
}

IProcessingLib::IProcessingLib(void)
{
}


IProcessingLib::~IProcessingLib(void)
{
}

IPROCESSINGLIB_API LONG_PTR __cdecl CreateCImage()
{
	return (LONG_PTR)(new CImage());
}

IPROCESSINGLIB_API bool __cdecl DestroyCImage(LONG_PTR CImg)
{
	CImage * Img = (CImage*) CImg;

	if (Img != NULL) delete Img;

	return true;
}

IPROCESSINGLIB_API bool __cdecl Load(LONG_PTR CImg, const char * filename)
{
	int _flag = false;
	CImage * Img = (CImage*) CImg;
	CString filenameCS;
	filenameCS = filename;

	std::cout << "Load(LONG_PTR CImg, CString filename)" << " | " << filename << " | " << filenameCS.GetString() << " | " << filenameCS << std::endl;

	if (Img != 0)
	{
		_flag = Img->Load(filename);
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

IPROCESSINGLIB_API bool __cdecl Save(LONG_PTR CImg, char * filename)
{
	int bFlag = false;
	CImage * Img = (CImage*) CImg;

	if (Img != 0)
	{
		bFlag = Img->Save(filename);
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

IPROCESSINGLIB_API HBITMAP* __cdecl GetBitmap(LONG_PTR CImg)
{
	CImage* Img = (CImage*)CImg;

	return (HBITMAP*)*(Img->GetBitmap());
}

IPROCESSINGLIB_API bool __cdecl aThreshold(LONG_PTR CImg,int n,double ff)
{
	CImage * Img = (CImage*) CImg;

	Threshold(Img, n, ff);
	
	return true;
}
