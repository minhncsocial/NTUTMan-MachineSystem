#include "mImage.h"

class mImage::Impl
{
public:
	/*int GetWidth()
	{
		return (mWidth);
	}*/
	void  Create(int _width,int _height,int _bits,DWORD _dwFlags=0);
 	BOOL  IsNull();
	void  Destroy();

	int   GetWidth();
	int   GetHeight();
	int   GetBPP();

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

mImage::mImage(void):mImpl(new mImage::Impl())
{
	mImpl->hBitmap = NULL;
	mImpl->hMemDC = NULL;
}

mImage::~mImage(void)
{
	Destroy();
}

//====================================================================================================
//                                         mImpl Functions
//====================================================================================================
int mImage::Impl::GetWidth()
{
	return (mWidth);
}

int mImage::Impl::GetHeight()
{
	return (mHeight);
}

void mImage::Impl::Create(int _width, int _height, int _bits, DWORD _dwFlags)
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

BOOL mImage::LoadBMP(LPCSTR filename)
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
	
	if (mImpl->mNumColors>0) 
	{
 		fread(ColorTab, 4, mImpl->mNumColors, fp);
		SetColorTable(0, mImpl->mNumColors, ColorTab);
	}

	fseek(fp, BFH.bfOffBits, SEEK_SET);
    fread(mImpl->lpBits, mImpl->mSize, 1, fp);
	fclose(fp);  

	return (TRUE);
}

BOOL mImage::SaveBMP(LPCSTR filename)
{
	BITMAPFILEHEADER BFH = {'MB',0,0,0,0};
    BITMAPINFOHEADER Bmih = {40,1,1,1,8,0,0,0,0,0,0};
	RGBQUAD	ColorTab[256];
	DWORD	dwBmiSize;
    FILE	*fp;

	dwBmiSize = 40 + 4*(mImpl->mNumColors);

	fp = fopen(filename, "w+b");
	if (fp == NULL)
		return (FALSE);

	BFH.bfSize    = sizeof(BITMAPFILEHEADER) + dwBmiSize + (mImpl->mSize);
	BFH.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (mImpl->mNumColors)*sizeof(RGBQUAD);
    
	Bmih.biWidth = mImpl->mWidth;
	Bmih.biHeight = mImpl->mHeight;
	Bmih.biBitCount = mImpl->mBitCount;

	fwrite(&BFH, 1, sizeof(BITMAPFILEHEADER), fp);
    fwrite((BYTE*)&Bmih, 1, 40, fp);
	if (mImpl->mBitCount <= 8) 
	{
		GetColorTable(0, mImpl->mNumColors, ColorTab);
		fwrite(ColorTab, 4, mImpl->mNumColors, fp);
	}

    fwrite(mImpl->lpBits, mImpl->mSize, 1, fp);
	fclose(fp);  

	return (TRUE);
}
//====================================================================================================
void mImage::Create(int _width, int _height, int _bits, DWORD _dwFlags)
{
	{
	//BITMAPINFOHEADER BIH = {40,0,0,1,0,0,0,0,0,0,0};
	//LPBITMAPINFO lpBmi;

	//mImpl->mWidth = _width;
	//mImpl->mHeight = _height;
	//mImpl->mBitCount = _bits;
	//mImpl->mBytesPerLine = (mImpl->mWidth*mImpl->mBitCount + 31)/32*4;
	//mImpl->mBytesPerPixel = mImpl->mBitCount/8;

	//if (mImpl->mBitCount > 8) mImpl->mNumColors = 0;
	//else  mImpl->mNumColors = 1 << (mImpl->mBitCount);
	//mImpl->mSize = (mImpl->mBytesPerLine)*(mImpl->mHeight);

	//BIH.biWidth = mImpl->mWidth;
	//BIH.biHeight = mImpl->mHeight;
	//BIH.biBitCount = mImpl->mBitCount;

	//lpBmi = (LPBITMAPINFO)malloc(40 + 4*(mImpl->mNumColors));
	//memcpy(lpBmi,&BIH,40);

	//mImpl->hBitmap = CreateDIBSection(NULL, lpBmi, DIB_RGB_COLORS, (VOID**) &mImpl->lpBits, NULL, 0);
	//free(lpBmi);
	}
	mImpl->Create(_width, _height, _bits, _dwFlags);
}

BOOL mImage::IsNull()
{
	if (mImpl->hBitmap == NULL)
		return (TRUE);
	else
		return (FALSE);
}

void  mImage::Destroy()
{
    if (mImpl->hBitmap != NULL) {
		DeleteObject(mImpl->hBitmap);
   		mImpl->hBitmap = NULL;
	}
}

int mImage::GetWidth()
{
	return (mImpl->mWidth);
	//return (mImpl->GetWidth());
}

int mImage::GetHeight()
{
	return (mImpl->mHeight);
}

int mImage::GetBPP()
{
	return (mImpl->mBitCount);
}

void  mImage::GetColorTable(int m, int n, RGBQUAD* ColorTab)
{
	HDC	hMemDC;

	hMemDC = CreateCompatibleDC(NULL); 
	SelectObject(hMemDC, mImpl->hBitmap);
	GetDIBColorTable(hMemDC, m, n, ColorTab);
	DeleteObject(hMemDC);
	DeleteDC(hMemDC);
}

void  mImage::SetColorTable(int m, int n, RGBQUAD* ColorTab)
{
	HDC	hMemDC;

	hMemDC = CreateCompatibleDC(NULL); 
	SelectObject(hMemDC, mImpl->hBitmap);
	SetDIBColorTable(hMemDC, m, n, ColorTab);
	DeleteObject(hMemDC);
	DeleteDC(hMemDC);
}

BYTE* mImage::GetPixelAddress(int x,int y)
{
	return ((mImpl->lpBits) + (mImpl->mHeight - 1 - y)*(mImpl->mBytesPerLine) + x*(mImpl->mBytesPerPixel));
}

COLORREF mImage::GetPixel(int x,int y )
{
	LPBYTE	lpBuf;
	DWORD	dwValue=0;
	RGBQUAD	ColorTab;

	lpBuf = (LPBYTE)(mImpl->lpBits)+(mImpl->mHeight - 1 - y)*(mImpl->mBytesPerLine) + x*(mImpl->mBytesPerPixel);
	memcpy(&dwValue, lpBuf, mImpl->mBytesPerPixel);
	if (mImpl->mBitCount <= 8)
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

int mImage::GetPitch()
{
	return (GetPixelAddress(0, 1) - GetPixelAddress(0, 0));
}

int mImage::GetMaxColorTableEntries()
{
	if (mImpl->mNumColors > 256) return (256);
	return (mImpl->mNumColors);
}

BOOL mImage::Load(const char * filename)
{
	BOOL bFlag = FALSE;
	char drive[_MAX_DRIVE];   
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];   
	char ext[_MAX_EXT];
	const char * filename1 = (const char*)(LPCTSTR)filename;

	_splitpath((const char*)(LPCTSTR)filename1, drive, dir, fname, ext);   

	if (! stricmp(ext, ".bmp"))	
		bFlag = LoadBMP(filename);

	return bFlag;
}

BOOL mImage::Save(const char * filename)
{
	BOOL bFlag = FALSE;
	char drive[_MAX_DRIVE];   
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];   
	char ext[_MAX_EXT];

	_splitpath((const char*)(LPCTSTR)filename, drive, dir, fname, ext);   

	if (! stricmp(ext, ".bmp"))	
		bFlag = SaveBMP(filename);

	return bFlag;
}

HBITMAP* mImage::GetBitmap()
{
	return(&mImpl->hBitmap);
}