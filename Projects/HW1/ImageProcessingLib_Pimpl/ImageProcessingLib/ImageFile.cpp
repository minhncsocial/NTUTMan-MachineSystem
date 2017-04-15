#include "ImageFile.h"

//--------------------------------------------------------------
//  BMP

//BOOL CImage::LoadBMP(LPCSTR lpstrFileName)
//{
//	BITMAPFILEHEADER BFH;
//    BITMAPINFOHEADER BIH;
//	RGBQUAD  ColorTab[256];
//    FILE	*fp;
//        
//	std::cout << "LoadBMP(LPCSTR lpstrFileName)" << " | " << lpstrFileName << std::endl;
//
//	fp=fopen(lpstrFileName,"rb");
//	if (fp==NULL)
//		return(FALSE);
//
//    fread(&BFH,sizeof(BITMAPFILEHEADER),1,fp);
//    fread(&BIH,sizeof(BITMAPINFOHEADER),1,fp);
//
//	if ((BFH.bfType!='MB')||(BIH.biCompression !=0)) {
//		fclose(fp);   
// 		return(FALSE);
//	}
// 
//	Create(BIH.biWidth,BIH.biHeight,BIH.biBitCount,0);
//
//    if (nNumColors>0) {
// 		fread(ColorTab,4,nNumColors,fp);
//		SetColorTable(0,nNumColors,ColorTab);
//	}
//
//	fseek(fp,BFH.bfOffBits,SEEK_SET);
//    fread(lpBits,nSize,1,fp);
//	fclose(fp);   
//   	return(TRUE);
//}
//
//BOOL CImage::SaveBMP(LPCSTR lpstrFileName)
//{
//	BITMAPFILEHEADER BFH={'MB',0,0,0,0};
//    BITMAPINFOHEADER Bmih={40,1,1,1,8,0,0,0,0,0,0};
//	RGBQUAD	ColorTab[256];
//	DWORD	dwBmiSize;
// 	FILE	*fp;
//      
//    dwBmiSize=40+4*nNumColors;
//
//	fp=fopen(lpstrFileName,"w+b");
//	if (fp==NULL)
//		return(FALSE);
//
//	BFH.bfSize   =sizeof(BITMAPFILEHEADER)+dwBmiSize+nSize;
//	BFH.bfOffBits=sizeof(BITMAPFILEHEADER)+
//		sizeof(BITMAPINFOHEADER)+nNumColors*sizeof(RGBQUAD);
//
//	Bmih.biWidth = nWidth;
//	Bmih.biHeight = nHeight;
//	Bmih.biBitCount = nBitCount;
//
//    fwrite(&BFH,1,sizeof(BITMAPFILEHEADER),fp);
//    fwrite((BYTE*)&Bmih,1,40,fp);
//	if (nBitCount<=8) {
//		GetColorTable(0,nNumColors,ColorTab);
//		fwrite(ColorTab,4,nNumColors,fp);
//	}
//    fwrite(lpBits,1,nSize,fp);
//	fclose(fp);
//   	return(TRUE);
//}
//  BMP