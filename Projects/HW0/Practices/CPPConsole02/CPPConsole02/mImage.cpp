#include "StdAfx.h"
#include "mImage.h"


mImage::mImage(void)
{
}


mImage::~mImage(void)
{
}

void mImage::Create(int Dx, int Dy, int Bits, DWORD dwFlags)
{
	BITMAPINFOHEADER BIH = {40,0,0,1,0,0,0,0,0,0,0};
	LPBITMAPINFO lpBmi;

	nWidth = Dx;
	nHeight = Dy;
	nBitCount = Bits;
	nBytesPerLine = (nWidth*nBitCount + 31)/32*4;
	nBytesPerPixel = nBitCount/8;
	if (nBitCount>8) nNumColors = 0;
	else nNumColors = 1<<nBitCount;
	nSize = nBytesPerLine*nHeight;

	BIH.biWidth = nWidth;
	BIH.biHeight = nHeight;
	BIH.biBitCount = nBitCount;

	lpBmi=(LPBITMAPINFO) malloc(40 + 4*nNumColors);
	memcpy(lpBmi, &BIH, 40);
	hBitmap=CreateDIBSection(NULL, lpBmi, DIB_RGB_COLORS, (VOID**)&lpBits, NULL, 0);

	free(lpBmi);
}

void mImage::SetColorTable(int m, int n, RGBQUAD* ColorTab)
{
	HDC hMemDC;

	hMemDC = CreateCompatibleDC(NULL); 
	SelectObject(hMemDC, hBitmap);
	SetDIBColorTable(hMemDC, m, n, ColorTab);
	DeleteObject(hMemDC);
	DeleteDC(hMemDC);
}

BOOL mImage::LoadBMP(char* filename)
{
	BITMAPFILEHEADER BFH;
	BITMAPINFOHEADER BIH;
	RGBQUAD ColorTab[256];
	FILE * fp;

	fp = fopen(filename,"rb");
	if (fp==NULL) return(FALSE);

	fread(&BFH, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&BIH, sizeof(BITMAPINFOHEADER), 1, fp);

	if ((BFH.bfType!='MB')||(BIH.biCompression !=0)) 
	{
		fclose(fp); 
		return (FALSE);
	}

	Create(BIH.biWidth,BIH.biHeight,BIH.biBitCount,0);

	if (nNumColors > 0) 
	{
		fread(ColorTab,4,nNumColors,fp);
		SetColorTable(0,nNumColors,ColorTab);
	}

	fseek(fp,BFH.bfOffBits,SEEK_SET);
	fread(lpBits,nSize,1,fp);
	fclose(fp);
	return (TRUE);
}

HBITMAP* mImage::GetBitmap()
{
	return (&hBitmap);
}
