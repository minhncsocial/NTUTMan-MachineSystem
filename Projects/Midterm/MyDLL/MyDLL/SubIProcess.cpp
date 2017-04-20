#include "stdafx.h"

//void GetImageParament(cmImage *pImg, struct IMAGEPARAMENT *ppImgParam)
//{
//	if (pImg->IsNull()) return;
//
//	ppImgParam->nWidth   = pImg->GetWidth();
//	ppImgParam->nHeight   = pImg->GetHeight();
//	ppImgParam->nBitCount  = pImg->GetBPP();
//	ppImgParam->nBytesPerLine   = (pImg->GetWidth()*pImg->GetBPP()+31)/32*4;
//	ppImgParam->nBytesPerPixel   = pImg->GetBPP()/8;
//	if (pImg->GetBPP()<=8) 
//		ppImgParam->nNumColors= 1 << pImg->GetBPP();
//	else 
//		ppImgParam->nNumColors= 0;
//	ppImgParam->nSize  = ppImgParam->nBytesPerLine*ppImgParam->nHeight;
//}

//=====================================================================

//void	ColorToGray(cmImage *pImgn, cmImage *pImgm)
//{
// 	int			i, x, y;
//	int			gray[256];
//	BYTE		*cbuf,*gbuf;
//	RGBQUAD		ColorTab[256];
// 	cmImage		gpImg;
// 	CString		str1;
// 	struct		IMAGEPARAMENT P;
//
//	GetImageParament(pImgm,&P);             
//	if (P.nBitCount<8) return;
// 
// 	gpImg.Create(P.nWidth,P.nHeight,8,0);   
//	for (i=0; i<256; i++)
//	{
//		ColorTab[i].rgbBlue = ColorTab[i].rgbGreen = 
//			                  ColorTab[i].rgbRed   = i;
//	}
//	gpImg.SetColorTable(0,256,ColorTab);    
//
//	if (pImgm->GetBPP()<=8) {               
// 		pImgm->GetColorTable(0,P.nNumColors,ColorTab);
//		for (i=0; i<P.nNumColors; i++)
//		{
//			gray[i] = (int) (0.11*ColorTab[i].rgbBlue + 
//				     0.59*ColorTab[i].rgbGreen + 0.30*ColorTab[i].rgbRed);
//		}
//		for (y=0; y<P.nHeight; y++) {
//			cbuf = (BYTE*) pImgm->GetPixelAddress(0,y); 
//			gbuf = (BYTE*) gpImg.GetPixelAddress(0,y);
//			for (x=0; x<P.nWidth; x++) 
//				gbuf[x] = (BYTE) gray[cbuf[x]];         
// 		}
//	} 
//	else {   
//		for (y=0; y<P.nHeight; y++) {
//			cbuf = (BYTE*) pImgm->GetPixelAddress(0,y); 
//			gbuf = (BYTE*) gpImg.GetPixelAddress(0,y);
//			for (x=0,i=0; x<P.nWidth; x++,i+=P.nBytesPerPixel) {
//				gbuf[x] = (BYTE) (0.11*cbuf[i] + 0.59*cbuf[i+1] + 0.30*cbuf[i+2]);
//			}
//		}
//	}
//
// 	ImageCopy(pImgn,&gpImg);
// 	gpImg.Destroy();
//}

//void	Threshold(cmImage *pImgm, int n, double ff)
//{
// 	struct	IMAGEPARAMENT P;
//	BYTE	**list,*lpBuf;
//	RGBQUAD	ColorTab[256];
//	long	pg[256];
// 	int		t,x,y,thre;
//	int		tab[256],buf[20],bn;
//    
// 	GetImageParament(pImgm,&P);              
//
//	list=(BYTE**) Create2DList(pImgm);
//	histog(list,pg,0,0,P.nWidth,P.nHeight);
// 
//	switch(n) {
//		case 1:
//			thre=FormAnalysis(pg,tab,buf,&bn);
// 			break;
//		case 2:
//			t=GrayImageType(pg);
//			if (t==1) ff=1.0-ff;
//			thre=Ptile(pg,ff);
//			break;
//		case 3:
//			thre=Otsu(pg);
//			break;
//		case 4:
//			thre=Minimum(pg);
//			break;
//		case 5:
//			thre=KSW_Entropic(pg);
//			break;
//		case 6:
//			thre=BiasNormal(pg);
//			break;
//		case 7:
//			thre=Moment(pg);
//			break;
//		case 8:
//			thre=ColligationThreshold(pg);
//			break;
//		case 9:
//			thre=SimpleThreshold(pg);
//			break;
//	}
//
// 	for (y=0;y<P.nHeight;y++) {
//		lpBuf=(BYTE*) pImgm->GetPixelAddress(0,y);
//		for (x=0;x<P.nWidth;x++,lpBuf++) {
//			if (*lpBuf>=thre) *lpBuf=1;
//			else		      *lpBuf=0;
//		}
//	}
// 	memset(ColorTab,0,1024);
//	SetAllPalette(pImgm,ColorTab);
//    SetPalette(pImgm,1,255,255,255);
//
//	Release2DList(list);
//}
