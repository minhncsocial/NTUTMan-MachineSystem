#include "IProcessing.h"


IPROCESSING_API int __cdecl testAdd(int a, int b)
{
	return (a + b);
}

IPROCESSING_API LONG_PTR __cdecl CreatecmImage()
{
	return (LONG_PTR)(new cmImage());
}

IPROCESSING_API bool __cdecl DestroycmImage(LONG_PTR _Img)
{
	cmImage * Img = (cmImage*) _Img;

	if (Img != NULL) delete Img;

	return true;
}

IPROCESSING_API bool __cdecl Load(LONG_PTR _Img, const char * filename)
{
	int _flag = false;
	cmImage * Img = (cmImage*) _Img;
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

IPROCESSING_API bool __cdecl Save(LONG_PTR _Img, char * filename)
{
	int bFlag = false;
	cmImage * Img = (cmImage*) _Img;

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

IPROCESSING_API HBITMAP* __cdecl GetBitmap(LONG_PTR _Img)
{
	cmImage* Img = (cmImage*)_Img;

	return (HBITMAP*)*(Img->GetBitmap());
}

IPROCESSING_API int __cdecl GetWidth(LONG_PTR _mImage)
{
	cmImage* Img = (cmImage*)_mImage;

	return (Img->GetWidth());
}

IPROCESSING_API int __cdecl GetHeight(LONG_PTR _mImage)
{
	cmImage* Img = (cmImage*)_mImage;

	return (Img->GetHeight());
}