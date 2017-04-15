// Image.cpp: implementation of the CImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
 
CImage::CImage()
{
	hBitmap=NULL;
	hMemDC=NULL;
}

CImage::~CImage()
{
	Destroy();
}

void CImage::Create(int Dx,int Dy,int Bits,DWORD dwFlags)
{
   BITMAPINFOHEADER BIH = {40,0,0,1,0,0,0,0,0,0,0  } ;
   LPBITMAPINFO	    lpBmi;
    
   nWidth = Dx;
   nHeight = Dy;
   nBitCount= Bits;
   nBytesPerLine = (nWidth*nBitCount+31)/32*4;
   nBytesPerPixel = nBitCount/8;
   if (nBitCount>8) nNumColors=0;
   else  nNumColors=1<<nBitCount;
   nSize=nBytesPerLine*nHeight;

   BIH.biWidth=nWidth;    
   BIH.biHeight=nHeight;	      
   BIH.biBitCount=nBitCount;
   
   lpBmi=(LPBITMAPINFO) malloc(40+4*nNumColors);
   memcpy(lpBmi,&BIH,40);
 
   hBitmap=CreateDIBSection(NULL,lpBmi,DIB_RGB_COLORS,
	                         (VOID**) &lpBits,NULL,0);
   free(lpBmi);
}

BOOL  CImage::IsNull()
{
	if (hBitmap==NULL)
		return(TRUE);
	else
		return(FALSE);
}

BOOL  CImage::Load(const CString csFileName)
{
	BOOL bFlag = FALSE;
	char drive[_MAX_DRIVE];   
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];   
	char ext[_MAX_EXT];
	const char * csFileName1 = (const char*)(LPCTSTR)csFileName;
	CStringA csFileName21(csFileName); // a helper string
	LPCSTR csFileName22 = csFileName21;
	LPCSTR csFileName3 = (LPCSTR)(LPCTSTR)csFileName;
 
	_splitpath((const char*)(LPCTSTR)csFileName1, drive, dir, fname, ext);  

	std::cout << "Load(const CString csFileName)" << " | " << csFileName.GetString() << " | " << (char *)csFileName1 << std::endl;

 	if (! stricmp(ext, ".bmp"))	
		bFlag=LoadBMP((char *)csFileName1);
 	//else if (! stricmp(ext, ".jpg")) 	
		//bFlag=LoadJPEG((char *)csFileName1);
 	else if (! stricmp(ext, ".tif")) 	
		bFlag=LoadTIF((char *)csFileName1);
 	else if (! stricmp(ext, ".gif")) 	
		bFlag=LoadGIF((char *)csFileName1);
 	else if (! stricmp(ext, ".pcx")) 	
		bFlag=LoadPCX((char *)csFileName1);
 	else if (! stricmp(ext, ".tga")) 	
		bFlag=LoadTGA((char *)csFileName1);
   	return(bFlag);
}

BOOL  CImage::Save(const CString csFileName)
{
	BOOL	bFlag = FALSE;
	char	drive[_MAX_DRIVE];   
	char	dir[_MAX_DIR];
	char	fname[_MAX_FNAME];   
	char	ext[_MAX_EXT];
       
	_splitpath((const char*)(LPCTSTR)csFileName, drive, dir, fname, ext);   

 	if (! stricmp(ext, ".bmp")) 	
		bFlag=SaveBMP((const char*)(LPCTSTR)csFileName);
 //	else if (! stricmp(ext, ".jpg")) 	
	//	bFlag=SaveJPEG(csFileName);
 	else if (! stricmp(ext, ".tif")) 	
		bFlag=SaveTIF((const char*)(LPCTSTR)csFileName);
 	else if (! stricmp(ext, ".gif")) 	
		bFlag=SaveGIF((const char*)(LPCTSTR)csFileName);
 	else if (! stricmp(ext, ".pcx")) 	
		bFlag=SavePCX((const char*)(LPCTSTR)csFileName);
 	else if (! stricmp(ext, ".tga")) 	
		bFlag=SaveTGA((const char*)(LPCTSTR)csFileName);
   	return(bFlag);
}

void  CImage::Destroy()
{
    if (hBitmap!=NULL) {
		DeleteObject(hBitmap);
   		hBitmap=NULL;
	}
}

BYTE* CImage::GetPixelAddress(int x,int y)
{
	return(lpBits+(nHeight-1-y)*nBytesPerLine+x*nBytesPerPixel);
}

COLORREF CImage::GetPixel(int x,int y)
{
	LPBYTE	lpBuf;
	DWORD	dwValue=0;
	RGBQUAD	ColorTab;

	lpBuf=(LPBYTE)lpBits+(nHeight-1-y)*nBytesPerLine+x*nBytesPerPixel;
	memcpy(&dwValue,lpBuf,nBytesPerPixel);
	if (nBitCount<=8) {
		GetColorTable(dwValue,1,&ColorTab);
		dwValue=RGB(ColorTab.rgbRed,
			    ColorTab.rgbGreen,ColorTab.rgbBlue);
	}
	else {
		dwValue=RGB((dwValue&0xff0000)>>16,
			    (dwValue&0xff00)>>8,dwValue&0xff);
	}
	return(dwValue);
}

int   CImage::GetWidth()
{
	return(nWidth);
}

int   CImage::GetHeight()
{
	return(nHeight);
}

int   CImage::GetBPP()
{
	return(nBitCount);
}

int	  CImage::GetPitch()
{
	return(GetPixelAddress(0,1)-GetPixelAddress(0,0));
} 

int	  CImage::GetMaxColorTableEntries()
{
	if (nNumColors>256) return(256);
	return(nNumColors);
}

void  CImage::GetColorTable(int m, int n, RGBQUAD* ColorTab)
{
	HDC		hMemDC;

    hMemDC =CreateCompatibleDC(NULL); 
    SelectObject(hMemDC,hBitmap);
 	GetDIBColorTable(hMemDC,m,n,ColorTab);
    DeleteObject(hMemDC);
	DeleteDC(hMemDC);
}

void  CImage::SetColorTable(int m, int n, RGBQUAD* ColorTab)
{
	HDC		hMemDC;

    hMemDC =CreateCompatibleDC(NULL); 
    SelectObject(hMemDC,hBitmap);
 	SetDIBColorTable(hMemDC,m,n,ColorTab);
    DeleteObject(hMemDC);
	DeleteDC(hMemDC);
}

HDC  CImage::GetDC()
{
   hMemDC =CreateCompatibleDC(NULL); 
   SelectObject(hMemDC,hBitmap);
   return hMemDC;
}

void CImage::ReleaseDC()
{
   if (hMemDC) {
      DeleteObject(hMemDC);
	  DeleteDC(hMemDC);
   }
}

BOOL  CImage::BitBlt(HDC hDestDC,int xDest,int yDest,
                     int nDestWidth,int nDestHeight,
					 int xSrc,int ySrc,DWORD dwROP) 
{
	HDC		hSrcDC;

	hSrcDC=GetDC();
	SelectObject(hSrcDC,hBitmap);
	::BitBlt(hDestDC,xDest,yDest,nDestWidth,nDestHeight,
		          hSrcDC,xSrc,ySrc,dwROP);
 	ReleaseDC();
   	return(TRUE);
}

BOOL  CImage::MaskBlt(HDC hDestDC,int xDest,int yDest,
			  HBITMAP hBitmap,DWORD dwROP)
{
	HDC		hDC=NULL,hSrcDC;

    hSrcDC = CreateCompatibleDC(hDC); 
    SelectObject(hSrcDC,hBitmap); 
	::BitBlt(hDestDC,xDest,yDest,nWidth,nHeight,
	          hSrcDC,xDest,yDest,dwROP);
    DeleteDC(hSrcDC); 
   	return(TRUE);
}

HBITMAP* CImage::GetBitmap()
{
    return(&hBitmap);
}