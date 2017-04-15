#include "IProcessing_Pimpl.h"


IPROCESSING_PIMPL_API int __cdecl testAdd(int a, int b)
{
	return (a + b);
}

IPROCESSING_PIMPL_API LONG_PTR __cdecl CreatemImage()
{
	return (LONG_PTR)(new mImage());
}

IPROCESSING_PIMPL_API bool __cdecl DestroyCImage(LONG_PTR _Img)
{
	mImage * Img = (mImage*) _Img;

	if (Img != NULL) delete Img;

	return true;
}

IPROCESSING_PIMPL_API bool __cdecl Load(LONG_PTR _Img, const char * filename)
{
	int _flag = false;
	mImage * Img = (mImage*) _Img;
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

IPROCESSING_PIMPL_API bool __cdecl Save(LONG_PTR _Img, char * filename)
{
	int bFlag = false;
	mImage * Img = (mImage*) _Img;

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

IPROCESSING_PIMPL_API HBITMAP* __cdecl GetBitmap(LONG_PTR _Img)
{
	mImage* Img = (mImage*)_Img;

	return (HBITMAP*)*(Img->GetBitmap());
}

IPROCESSING_PIMPL_API int __cdecl GetWidth(LONG_PTR _mImage)
{
	mImage* Img = (mImage*)_mImage;

	return (Img->GetWidth());
}