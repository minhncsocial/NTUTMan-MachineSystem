#include "stdafx.h"
#include "cmImage.h"


cmImage::cmImage(void)
{
}

cmImage::~cmImage(void)
{
}

////=============================================================================
////............................
////=============================================================================
//void cmImage::Create(int _width, int _height, int _bits, DWORD _dwFlags)
//{
//	BITMAPINFOHEADER BIH = {40,0,0,1,0,0,0,0,0,0,0};
//	LPBITMAPINFO lpBmi;
//
//	mWidth = _width;
//	mHeight = _height;
//	mBitCount= _bits;
//	mBytesPerLine = (mWidth*mBitCount + 31)/32*4;
//	mBytesPerPixel = mBitCount/8;
//
//	if (mBitCount>8) mNumColors = 0;
//	else mNumColors = 1<<mBitCount;
//	mSize = mBytesPerLine*mHeight;
//
//	BIH.biWidth = mWidth;    
//	BIH.biHeight = mHeight;	      
//	BIH.biBitCount = mBitCount;
//
//	lpBmi = (LPBITMAPINFO) malloc(40 + 4*mNumColors);
//	memcpy(lpBmi, &BIH, 40);
//
//	hBitmap = CreateDIBSection(NULL, lpBmi, DIB_RGB_COLORS, (VOID**)&lpBits, NULL, 0);
//
//	free(lpBmi);
//}
//
//
////=============================================================================
////............................
////=============================================================================
//BOOL cmImage::LoadBMP(char * filename)
//{
//	BITMAPFILEHEADER BFH;
//    BITMAPINFOHEADER BIH;
//	RGBQUAD ColorTab[256];
//	FILE * file;
//
//	file = fopen(filename, "rb");
//	// If empty file return FALSE
//	if (file == NULL) return FALSE;
//
//	fread(&BFH,sizeof(BITMAPFILEHEADER),1,file);
//    fread(&BIH,sizeof(BITMAPINFOHEADER),1,file);
//
//	// Unknown why ???
//	if ((BFH.bfType!='MB')||(BIH.biCompression !=0)) {
//		fclose(file);   
// 		return(FALSE);
//	}
//
//	//Create(BIH.biWidth,BIH.biHeight,BIH.biBitCount,0); // INTERNAL FUNC
//
//	// multi-color image: divide int to planes ???
//    if (mNumColors>0) {
// 		fread(ColorTab, 4, mNumColors, file);
//		//SetColorTable(0,nNumColors,ColorTab); // INTERNAL FUNC
//	}
//
//	fseek(file, BFH.bfOffBits, SEEK_SET);
//	fread(lpBits, mSize, 1, file);
//	fclose(file);
//
//	return(TRUE);
//}
