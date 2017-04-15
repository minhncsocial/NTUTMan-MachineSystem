#include "cmImage.h"

//=======================================================================
// BEGIN: cmImage::Impl
class cmImage::Impl
{
public:
	void  Create(int _width, int _height, int _bits, DWORD _dwFlags=0);
 	BOOL  IsNull();
	void  Destroy();

	int   GetWidth();
	int   GetHeight();
	int   GetBPP();
	
	void  GetColorTable(int m, int n, RGBQUAD* ColorTab);
	void  SetColorTable(int m, int n, RGBQUAD* ColorTab);
	BYTE* GetPixelAddress(int x, int y);
	COLORREF GetPixel(int x, int y );

	int	  GetPitch();
	int	  GetMaxColorTableEntries();

	BOOL  LoadBMP(LPCSTR filename);
	BOOL  SaveBMP(LPCSTR filename);

public:
	HBITMAP			hBitmap;
 	LPBYTE    		lpBits;

	int				mWidth;
	int				mHeight;
	int				mBitCount;
    int				mBytesPerLine;
	int				mBytesPerPixel;
	int				mNumColors;
	int				mSize;

	HDC				hMemDC;
};

void  cmImage::Impl::Create(int _width, int _height, int _bits, DWORD _dwFlags)
{
	BITMAPINFOHEADER BIH = {40,0,0,1,0,0,0,0,0,0,0};
	LPBITMAPINFO lpBmi;

	mWidth = _width;
	mHeight = _height;
	mBitCount = _bits;
	mBytesPerLine = (mWidth*mBitCount + 31)/32*4;
	mBytesPerPixel = mBitCount/8;

	if (mBitCount > 8) mNumColors = 0;
	else  mNumColors = 1 << (mBitCount);
	mSize = (mBytesPerLine)*(mHeight);

	BIH.biWidth = mWidth;
	BIH.biHeight = mHeight;
	BIH.biBitCount = mBitCount;

	lpBmi = (LPBITMAPINFO)malloc(40 + 4*(mNumColors));
	memcpy(lpBmi,&BIH,40);

	hBitmap = CreateDIBSection(NULL, lpBmi, DIB_RGB_COLORS, (VOID**) &lpBits, NULL, 0);
	free(lpBmi);
}

BOOL  cmImage::Impl::IsNull()
{
	if (hBitmap == NULL)
		return (TRUE);
	else
		return (FALSE);
}

void  cmImage::Impl::Destroy()
{
    if (hBitmap != NULL) 
	{
		DeleteObject(hBitmap);
   		hBitmap = NULL;
	}
}

int   cmImage::Impl::GetWidth()
{
	return (mWidth);
}
int   cmImage::Impl::GetHeight()
{
	return (mHeight);
}
int   cmImage::Impl::GetBPP()
{
	return (mBitCount);
}
	
void  cmImage::Impl::GetColorTable(int m, int n, RGBQUAD* ColorTab)
{
	HDC	hMemDC;

	hMemDC = CreateCompatibleDC(NULL); 
	SelectObject(hMemDC, hBitmap);
	GetDIBColorTable(hMemDC, m, n, ColorTab);
	DeleteObject(hMemDC);
	DeleteDC(hMemDC);
}
void  cmImage::Impl::SetColorTable(int m, int n, RGBQUAD* ColorTab)
{
	HDC	hMemDC;

	hMemDC = CreateCompatibleDC(NULL); 
	SelectObject(hMemDC, hBitmap);
	SetDIBColorTable(hMemDC, m, n, ColorTab);
	DeleteObject(hMemDC);
	DeleteDC(hMemDC);
}
BYTE* cmImage::Impl::GetPixelAddress(int x,int y)
{
	return (lpBits + (mHeight - 1 - y)*mBytesPerLine + x*mBytesPerPixel);
}
COLORREF cmImage::Impl::GetPixel(int x,int y )
{
	LPBYTE	lpBuf;
	DWORD	dwValue=0;
	RGBQUAD	ColorTab;

	lpBuf = (LPBYTE)(lpBits)+(mHeight - 1 - y)*mBytesPerLine + x*mBytesPerPixel;
	memcpy(&dwValue, lpBuf, mBytesPerPixel);
	if (mBitCount <= 8)
	{
		GetColorTable(dwValue, 1, &ColorTab);
		dwValue = RGB(ColorTab.rgbRed, ColorTab.rgbGreen, ColorTab.rgbBlue);
	}
	else
	{
		dwValue = RGB((dwValue & 0xff0000)>>16, (dwValue & 0xff00)>>8, dwValue & 0xff);
	}

	return (dwValue);
}

int	  cmImage::Impl::GetPitch()
{
	return (GetPixelAddress(0, 1) - GetPixelAddress(0, 0));
}
int	  cmImage::Impl::GetMaxColorTableEntries()
{
	if (mNumColors > 256) return (256);
	return (mNumColors);
}

BOOL  cmImage::Impl::LoadBMP(LPCSTR filename)
{
	BITMAPFILEHEADER BFH;
    BITMAPINFOHEADER BIH;
	RGBQUAD	ColorTab[256];
    FILE	*fp;

	fp=fopen(filename, "rb");
	if (fp == NULL)
		return (FALSE);

	fread(&BFH, sizeof(BITMAPFILEHEADER), 1, fp);
    fread(&BIH, sizeof(BITMAPINFOHEADER), 1, fp);

	if ((BFH.bfType != 'MB')||(BIH.biCompression != 0)) 
	{
		fclose(fp);
 		return (FALSE);
	}

	Create(BIH.biWidth, BIH.biHeight, BIH.biBitCount, 0);
	
	if (mNumColors>0) 
	{
 		fread(ColorTab, 4, mNumColors, fp);
		SetColorTable(0, mNumColors, ColorTab);
	}

	fseek(fp, BFH.bfOffBits, SEEK_SET);
    fread(lpBits, mSize, 1, fp);
	fclose(fp);  

	return (TRUE);
}
BOOL  cmImage::Impl::SaveBMP(LPCSTR filename)
{
	BITMAPFILEHEADER BFH = {'MB',0,0,0,0};
    BITMAPINFOHEADER Bmih = {40,1,1,1,8,0,0,0,0,0,0};
	RGBQUAD	ColorTab[256];
	DWORD	dwBmiSize;
    FILE	*fp;

	dwBmiSize = 40 + 4*mNumColors;

	fp = fopen(filename, "w+b");
	if (fp == NULL)
		return (FALSE);

	BFH.bfSize    = sizeof(BITMAPFILEHEADER) + dwBmiSize + mSize;
	BFH.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + mNumColors*sizeof(RGBQUAD);
    
	Bmih.biWidth = mWidth;
	Bmih.biHeight = mHeight;
	Bmih.biBitCount = mBitCount;

	fwrite(&BFH, 1, sizeof(BITMAPFILEHEADER), fp);
    fwrite((BYTE*)&Bmih, 1, 40, fp);
	if (mBitCount <= 8) 
	{
		GetColorTable(0, mNumColors, ColorTab);
		fwrite(ColorTab, 4, mNumColors, fp);
	}

    fwrite(lpBits, mSize, 1, fp);
	fclose(fp);  

	return (TRUE);
}

// END: cmImage::Impl
//=======================================================================


//=======================================================================
// BEGIN: cmImage
cmImage::cmImage(void):mImpl(new cmImage::Impl())
{
	mImpl->hBitmap = NULL;
	mImpl->hMemDC = NULL;
}

cmImage::~cmImage(void)
{
	mImpl->Destroy();
}

int   cmImage::GetWidth()
{
	return (mImpl->mWidth);
}

int   cmImage::GetHeight()
{
	return (mImpl->mHeight);
}

BOOL cmImage::Load(const char * filename)
{
	BOOL bFlag = FALSE;
	char drive[_MAX_DRIVE];   
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];   
	char ext[_MAX_EXT];
	const char * filename1 = (const char*)(LPCTSTR)filename;

	_splitpath((const char*)(LPCTSTR)filename1, drive, dir, fname, ext);   

	if (! stricmp(ext, ".bmp"))	
		bFlag = mImpl->LoadBMP(filename);

	return bFlag;
}

BOOL cmImage::Save(const char * filename)
{
	BOOL bFlag = FALSE;
	char drive[_MAX_DRIVE];   
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];   
	char ext[_MAX_EXT];

	_splitpath((const char*)(LPCTSTR)filename, drive, dir, fname, ext);   

	if (! stricmp(ext, ".bmp"))	
		bFlag = mImpl->SaveBMP(filename);

	return bFlag;
}

HBITMAP* cmImage::GetBitmap()
{
	return(&mImpl->hBitmap);
}

// END: cmImage::Impl
//=======================================================================