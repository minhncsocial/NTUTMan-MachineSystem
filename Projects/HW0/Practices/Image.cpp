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

//--------------------------------------------------------------
//  BMP

BOOL CImage::LoadBMP(char* filename)
{
	BITMAPFILEHEADER BFH;
    BITMAPINFOHEADER BIH;
	RGBQUAD  ColorTab[256];
    FILE	*fp;
        
	fp=fopen(filename,"rb");
	if (fp==NULL)
		return(FALSE);

    fread(&BFH,sizeof(BITMAPFILEHEADER),1,fp);
    fread(&BIH,sizeof(BITMAPINFOHEADER),1,fp);

	if ((BFH.bfType!='MB')||(BIH.biCompression !=0)) {
		fclose(fp);   
 		return(FALSE);
	}
 
	Create(BIH.biWidth,BIH.biHeight,BIH.biBitCount,0);

    if (nNumColors>0) {
 		fread(ColorTab,4,nNumColors,fp);
		SetColorTable(0,nNumColors,ColorTab);
	}

	fseek(fp,BFH.bfOffBits,SEEK_SET);
    fread(lpBits,nSize,1,fp);
	fclose(fp);   
   	return(TRUE);
}

BOOL CImage::SaveBMP(char* filename)
{
	BITMAPFILEHEADER BFH={'MB',0,0,0,0};
    BITMAPINFOHEADER Bmih={40,1,1,1,8,0,0,0,0,0,0};
	RGBQUAD	ColorTab[256];
	DWORD	dwBmiSize;
 	FILE	*fp;
      
    dwBmiSize=40+4*nNumColors;

	fp=fopen(filename,"w+b");
	if (fp==NULL)
		return(FALSE);

	BFH.bfSize   =sizeof(BITMAPFILEHEADER)+dwBmiSize+nSize;
	BFH.bfOffBits=sizeof(BITMAPFILEHEADER)+
		sizeof(BITMAPINFOHEADER)+nNumColors*sizeof(RGBQUAD);

	Bmih.biWidth = nWidth;
	Bmih.biHeight = nHeight;
	Bmih.biBitCount = nBitCount;

    fwrite(&BFH,1,sizeof(BITMAPFILEHEADER),fp);
    fwrite((BYTE*)&Bmih,1,40,fp);
	if (nBitCount<=8) {
		GetColorTable(0,nNumColors,ColorTab);
		fwrite(ColorTab,4,nNumColors,fp);
	}
    fwrite(lpBits,1,nSize,fp);
	fclose(fp);
   	return(TRUE);
}
//  BMP

HBITMAP* CImage::GetBitmap()
{
    return(&hBitmap);
}

 