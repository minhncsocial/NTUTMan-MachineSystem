#include "MyDLL.h"


MYDLL_API int __cdecl fnMyDLL(int a, int b)
{
	return (a + b);
}

MYDLL_API LONG_PTR __cdecl CreateCImage()
{
	return (LONG_PTR)(new cmImage());
}

MYDLL_API bool __cdecl DestroyCImage(LONG_PTR _Img)
{
	cmImage * Img = (cmImage*) _Img;

	if (Img != NULL) delete Img;

	return true;
}

MYDLL_API bool __cdecl LoadBMP(LONG_PTR _Img, const char * filename)
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

MYDLL_API bool __cdecl Save(LONG_PTR _Img, char * filename)
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

MYDLL_API HBITMAP* __cdecl GetBitmap(LONG_PTR _Img)
{
	cmImage* Img = (cmImage*)_Img;

	return (HBITMAP*)*(Img->GetBitmap());
}

MYDLL_API int __cdecl GetWidth(LONG_PTR _mImage)
{
	cmImage* Img = (cmImage*)_mImage;

	return (Img->GetWidth());
}

MYDLL_API int __cdecl GetHeight(LONG_PTR _mImage)
{
	cmImage* Img = (cmImage*)_mImage;

	return (Img->GetHeight());
}

MYDLL_API BOOL __cdecl DoBitBlt(LONG_PTR _mImage, LONG_PTR hDC)
{
	cmImage* Img = (cmImage*)_mImage;

	return (Img->BitBlt(HDC(hDC), 0, 0,
                      Img->GetWidth(), Img->GetHeight(),
					  0, 0, SRCCOPY));
}

MYDLL_API void __cdecl ColorToGray(LONG_PTR destImage, LONG_PTR srcImage)
{
	cmImage* destImg = (cmImage*)destImage;
	cmImage* srcImg = (cmImage*)srcImage;


}