// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////

#ifndef		_CIMAGE_H
#define		_CIMAGE_H

#include "stdafx.h"

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

class CImage : public CObject    
{
private:
	HBITMAP			hBitmap;
 	LPBYTE    		lpBits;

	int				nWidth;
	int				nHeight;
	int				nBitCount;
    int				nBytesPerLine;
	int				nBytesPerPixel;
	int				nNumColors;
	int				nSize;

	HDC				hMemDC;

public:
	CImage();
 	~CImage();
public:

// Overrides
 	virtual BOOL  BitBlt(HDC,int,int,int,int,int,int,DWORD);
 	virtual BOOL  MaskBlt(HDC,int,int,HBITMAP,DWORD);
  	virtual HDC   GetDC();
	virtual void  ReleaseDC();

	void  Create(int Width,int Height,int Bits,DWORD dwFlags=0);
 	BOOL  IsNull();
	BOOL  Load(const CString pszFilename);
	BOOL  Save(const CString pszFilename);
	void  Destroy();

	int   GetWidth();
	int   GetHeight();
	int   GetBPP();
	int	  GetPitch();
	int	  GetMaxColorTableEntries();
  
	BYTE* GetPixelAddress(int x,int y);
	COLORREF GetPixel(int x,int y );
	void  GetColorTable(int m, int n, RGBQUAD* ColorTab);
	void  SetColorTable(int m, int n, RGBQUAD* ColorTab);

	BOOL  LoadBMP(LPCSTR lpstrFileName);
 	BOOL  LoadTIF(LPCSTR lpstrFileName);
	BOOL  LoadGIF(LPCSTR lpstrFileName);
	BOOL  LoadPCX(LPCSTR lpstrFileName);
 	BOOL  LoadTGA(LPCSTR lpstrFileName);
	BOOL  LoadJPEG(LPCSTR lpstrFileName);
 
	BOOL  SaveBMP(LPCSTR lpstrFileName);
	BOOL  SaveTIF(LPCSTR lpstrFileName);
	BOOL  SaveGIF(LPCSTR lpstrFileName);
	BOOL  SavePCX(LPCSTR lpstrFileName);
	BOOL  SaveTGA(LPCSTR lpstrFileName);
	BOOL  SaveJPEG(LPCSTR lpstrFileName); 
};

#endif		//!_CIMAGE_H

