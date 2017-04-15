//   IProcessE.cpp

#include "stdafx.h"
     
#ifndef		_INC_IPROCESSEC
#define		_INC_IPROCESSEC

int		nSobelFlag=0;

void Morphologic(CImage *pImg0,CImage *pImg1,int n)
{
 	struct	IMAGEPARAMENT P;
 	BYTE	**list1,**list0;
	int		k;
	CImage  gImg1,gImg0;
   
	k=ImageType(pImg1);
 	if (k==2)
		Threshold(pImg1,1,0);
	else if (k!=0) return;
 
 	ExpandImage(&gImg1,pImg1);
	ImageCopy(&gImg0,&gImg1);
 	list1=(BYTE**) Create2DList(&gImg1);
	list0=(BYTE**) Create2DList(&gImg0);
 
 	GetImageParament(&gImg1,&P); 
 	switch(n) {
		case 1:
			Erosion(list0,list1,P.nWidth,P.nHeight);
			break;
		case 2:
			Dilation(list0,list1,P.nWidth,P.nHeight);
			break;
		case 3:
			Inneredge(list0,list1,P.nWidth,P.nHeight);
			break;
		case 4:
			Outteredge(list0,list1,P.nWidth,P.nHeight);
			break;
		case 5:
			Morphologyedge(list0,list1,P.nWidth,P.nHeight);
			break;
		case 6:
			Skeleton(list0,list1,P.nWidth,P.nHeight);
			break;
		case 7:
			Erosion(list0,list1,P.nWidth,P.nHeight);
			Dilation(list1,list0,P.nBytesPerLine,P.nHeight);
 			break;
		case 8:
			Dilation(list0,list1,P.nWidth,P.nHeight);
			Erosion(list1,list0,P.nBytesPerLine,P.nHeight);
 			break;
		case 9:
			MorphologyThin(list0,list1,P.nWidth,P.nHeight);
   			break;		
		case 10:
  		    PatternThin(list1,P.nWidth,P.nHeight);
  			break;		
	}
	Release2DList(list1);
	Release2DList(list0);

    if (n<7)
		ReduceImage(pImg1,&gImg0);
	else
		ReduceImage(pImg1,&gImg1);
 
	gImg1.Destroy();
	gImg0.Destroy();
}

void GMorphologic(CImage *pImg0,CImage *pImg1,int n)
{
 	struct	IMAGEPARAMENT P;
 	BYTE	**list1,**list0;
	CImage  gImg1,gImg0;
	RGBQUAD	ColorTab[256];
  
 	ExpandImage(&gImg1,pImg1);
	ImageCopy(&gImg0,&gImg1);
 	list1=(BYTE**) Create2DList(&gImg1);
	list0=(BYTE**) Create2DList(&gImg0);
 
 	GetImageParament(&gImg1,&P); 
	switch(n) {
		case 1:
			GErosion(list0,list1,P.nWidth,P.nHeight);
			break;
		case 2:
			GDilation(list0,list1,P.nWidth,P.nHeight);
			break;
		case 3:
			GErosion(list0,list1,P.nWidth,P.nHeight);
			GDilation(list1,list0,P.nBytesPerLine,P.nHeight);
 			break;
		case 4:
			GDilation(list0,list1,P.nWidth,P.nHeight);
			GErosion(list1,list0,P.nBytesPerLine,P.nHeight);
 			break;
		case 5:
			GGrad(list0,list1,P.nWidth,P.nHeight);
			break;
		case 6:
			GIBorder(list0,list1,P.nWidth,P.nHeight);
			break;
		case 7:
			GOBorder(list0,list1,P.nWidth,P.nHeight);
			break;
		case 8:
			GTopHat(list0,list1,P.nWidth,P.nHeight);
			break;
		case 9:
			GBlackTopHat(list0,list1,P.nWidth,P.nHeight);
			break;
	}
	Release2DList(list1);
	Release2DList(list0);

    if ((n==3)||(n==4))
		ReduceImage(pImg1,&gImg1);
	else
		ReduceImage(pImg1,&gImg0);
	gImg1.Destroy();
	gImg0.Destroy();

	if (n>7) {
 		memset(ColorTab,0,1024);
		SetAllPalette(pImg1,ColorTab);
		SetPalette(pImg1,1,255,255,255);
	}
}

int  ColorHistogram(CImage *pImg,int x,int y,int Dx,int Dy,long *pg,int n)
{
 	struct	IMAGEPARAMENT P;
	int		i,j,dp=0;
	BYTE	*buf;

	GetImageParament(pImg,&P);
	buf=(BYTE*) malloc(P.nBytesPerLine);
  	for (i=0;i<256;i++)  pg[i]=0;
	for(i=y;i<y+Dy;i++) 
	{
		GetRectValue(pImg,0,i,P.nWidth,1,buf);
		if (n>3)
 			RgbToHsv(buf,buf,P.nWidth);
		switch(n) {
			case 1:
			case 4:
 				for (j=x;j<x+Dx;j++) pg[buf[j*P.nBytesPerPixel]]++;	
				break;
			case 2:
 			case 5:
				for (j=x;j<x+Dx;j++) pg[buf[j*P.nBytesPerPixel+1]]++;	
				break;
			case 3:
 			case 6:
				for (j=x;j<x+Dx;j++) pg[buf[j*P.nBytesPerPixel+2]]++;	
				break;
		}
	}
	free(buf);

	if (n==4) 
	    dp=HueHistogShift(pg);
	return(dp);
}

void ToRGB(CImage *pImgn,CImage *pImgm,int n)
{
 	struct	IMAGEPARAMENT P;
 	int	    i,x,y;
 	BYTE	*buf;

 	GetImageParament(pImgm,&P);
	pImgn->Destroy();
	pImgn->Create(P.nWidth,P.nHeight,8,0);
  
	buf =(BYTE*) malloc(P.nBytesPerLine);
	for (y=0;y<P.nHeight;y++) {
		GetRectValue(pImgm,0,y,P.nWidth,1,buf);
 		for (x=0,i=0;x<P.nWidth;x++,i+=P.nBytesPerPixel) {
			if (n==0)
				buf[x]=buf[i];
			else if (n==1)
				buf[x]=buf[i+1];
			else
 				buf[x]=buf[i+2];
 		}
		SetRectValue(pImgn,0,y,P.nWidth,1,buf);
 	}
 	free(buf);

	for (i=0;i<256;i++) {
		if (n==0)
			SetPalette(pImgn,i,0,0,i);
		else if (n==1)
			SetPalette(pImgn,i,0,i,0);
		else 
			SetPalette(pImgn,i,i,0,0);
	}
}

void ToHSV(CImage *pImgn,CImage *pImgm,int n)
{
 	struct	IMAGEPARAMENT P;
 	int	    i,x,y;
 	BYTE	*buf,bufp[4];

 	GetImageParament(pImgm,&P);
	pImgn->Destroy();
	pImgn->Create(P.nWidth,P.nHeight,8,0);
  
	buf =(BYTE*) malloc(P.nBytesPerLine);
	for (y=0;y<P.nHeight;y++) {
		GetRectValue(pImgm,0,y,P.nWidth,1,buf);
 		RgbToHsv(buf,buf,P.nWidth);
		for (x=0,i=0;x<P.nWidth;x++,i+=P.nBytesPerPixel) {
			switch(n) {
				case 0 :  
					buf[x]=buf[i];
					break;
				case 1 :  
					buf[x]=buf[i+1];
					break;
				case 2 :
					buf[x]=buf[i+2];
					break;
			}
		}
		SetRectValue(pImgn,0,y,P.nWidth,1,buf);
 	}
 	free(buf);

	if (n==0) {
		for (i=0;i<256;i++) {
			bufp[0]=i;
			bufp[1]=bufp[2]=255;
			HsvToRgb(bufp,bufp,1);
			SetPalette(pImgn,i,(int) bufp[2],(int) bufp[1],(int) bufp[0]);
		}
	}
	else {
		for (i=0;i<256;i++) 
			SetPalette(pImgn,i,i,i,i);
	}
}

void ToYIQLAB(CImage *pImgn,CImage *pImgm,int n)
{
 	struct	IMAGEPARAMENT P;
 	int	    i,x,y;
 	BYTE	*buf;

 	GetImageParament(pImgm,&P);
	pImgn->Destroy();
	pImgn->Create(P.nWidth,P.nHeight,8,0);
  
	buf =(BYTE*) malloc(P.nBytesPerLine);
	for (y=0;y<P.nHeight;y++) {
		GetRectValue(pImgm,0,y,P.nWidth,1,buf);
		if (n<3)
 			RgbToYiq(buf,buf,P.nWidth);
		else
 			RgbToLab(buf,buf,P.nWidth);
		for (x=0,i=0;x<P.nWidth;x++,i+=P.nBytesPerPixel) {
			switch(n%3) {
				case 0 :  
					buf[x]=buf[i];
					break;
				case 1 :  
					buf[x]=buf[i+1];
					break;
				case 2 :
					buf[x]=buf[i+2];
					break;
			}
		}
		SetRectValue(pImgn,0,y,P.nWidth,1,buf);
 	}
 	free(buf);

	for (i=0;i<256;i++) 
		SetPalette(pImgn,i,i,i,i);
}

void ColorSobel(CImage *pImgn,CImage *pImgm,int n)
{
 	struct	IMAGEPARAMENT P,Ps;
 	int	    i,k,x,y;
 	BYTE	*buf;
	BYTE	**listS,**listR,**listG,**listB;
	BYTE	*bufR,*bufG,*bufB;
 
 	GetImageParament(pImgm,&P);

	pImgn->Destroy();
	pImgn->Create(P.nWidth,P.nHeight,8,0);
	listS=Create2DList(pImgn);  
	listR=(BYTE**)malloc(P.nHeight*sizeof(BYTE*));
	listG=(BYTE**)malloc(P.nHeight*sizeof(BYTE*));
	listB=(BYTE**)malloc(P.nHeight*sizeof(BYTE*));

	GetImageParament(pImgn,&Ps);
	bufR=(BYTE*) malloc(Ps.nBytesPerLine*Ps.nHeight);
	bufG=(BYTE*) malloc(Ps.nBytesPerLine*Ps.nHeight);
	bufB=(BYTE*) malloc(Ps.nBytesPerLine*Ps.nHeight);
	for(i=0;i<P.nHeight;i++) {
		listR[Ps.nHeight-1-i]=bufR+i*Ps.nBytesPerLine;
		listG[Ps.nHeight-1-i]=bufG+i*Ps.nBytesPerLine;
		listB[Ps.nHeight-1-i]=bufB+i*Ps.nBytesPerLine;
 	}

 	buf =(BYTE*) malloc(P.nBytesPerLine);
	for (y=0;y<P.nHeight;y++) {
		GetRectValue(pImgm,0,y,P.nWidth,1,buf);
		if (nSobelFlag==1) 
			RgbToYiq(buf,buf,P.nWidth);
		if (nSobelFlag==2) 
			RgbToLab(buf,buf,P.nWidth);
 		for (x=0,i=0;x<P.nWidth;x++,i+=P.nBytesPerPixel) {
			listB[y][x]=buf[i]; 
			listG[y][x]=buf[i+1]; 
			listR[y][x]=buf[i+2]; 
		}
  	}
 	free(buf);

	Sobel(listS,listR,Ps.nWidth,Ps.nHeight);
 	memcpy(bufR,&listS[Ps.nHeight-1][0],Ps.nSize);
	Sobel(listS,listG,Ps.nWidth,Ps.nHeight);
 	memcpy(bufG,&listS[Ps.nHeight-1][0],Ps.nSize);
 	Sobel(listS,listB,Ps.nWidth,Ps.nHeight);
 	memcpy(bufB,&listS[Ps.nHeight-1][0],Ps.nSize);

	for (y=0;y<P.nHeight;y++) {
		int		r,g,b;

 		for (x=0;x<P.nWidth;x++) {
			if (n==0) {
				k = (listR[y][x]>listG[y][x])?listR[y][x]:listG[y][x];
				listS[y][x]= (k>listB[y][x])? k : listB[y][x];
 			}
			else if (n==1) {
				k=listR[y][x]+listG[y][x]+listB[y][x];
				if (k>255) k=255;
				listS[y][x]=k;
  			}
			else {
				r=listR[y][x];
				g=listG[y][x];
				b=listB[y][x];
				k=(int) sqrt((double)(r*r+g*g+b*b));
				if (k>255) k=255;
				listS[y][x]=k;
			}
		}
  	}
 
	for (i=0;i<256;i++) 
		SetPalette(pImgn,i,i,i,i);
 
 	free(listR);
	free(listG);
	free(listB);
	free(bufR);
	free(bufG);
	free(bufB);
	Release2DList(listS);
}

void RemoveBackgrond(CImage *pImgn,CImage *pImgm)
{
	BITMAPINFOHEADER bmi={40,0,0,1,1,0,0,0,0,0,0};
 	struct	IMAGEPARAMENT Pm,Pn;
	LPBITMAPINFO	lpBmi;
	HDC				hMemDC;
	HBITMAP			hbmMask;
	BYTE			*lpBits,*lpbuf;
	RGBQUAD			ColorTab[2]={{0,0,0},{255,255,255}};

 	GetImageParament(pImgm,&Pm);
  	GetImageParament(pImgn,&Pn);
	if ((Pm.nWidth!=Pn.nWidth)||(Pm.nHeight!=Pn.nHeight)) 
		return;

	bmi.biWidth = Pm.nWidth;
	bmi.biHeight = Pm.nHeight ;
	lpBmi=(LPBITMAPINFO) malloc(48);
	memcpy(lpBmi,&bmi,40);
	memcpy(lpBmi->bmiColors,ColorTab,8);
	
	hbmMask=CreateDIBSection(NULL,lpBmi,DIB_RGB_COLORS,(VOID**)&lpBits,NULL,0);

	lpbuf=(BYTE*) pImgn->GetPixelAddress(0,Pn.nHeight-1);
	memcpy(lpBits,lpbuf,Pn.nSize);

	hMemDC=pImgm->GetDC();
 	pImgm->MaskBlt(hMemDC,0,0,hbmMask,SRCAND);
 	pImgm->ReleaseDC();

	DeleteObject(hbmMask);
	free(lpBmi);
}

void AddImage(CImage *pImgn,CImage *pImgm)
{
 	struct	IMAGEPARAMENT  Pm,P;
 	int		i,j,k;
	BYTE	*bufm,*bufn;

 	GetImageParament(pImgm,&Pm);
  	GetImageParament(pImgn,&P);
	if ((Pm.nWidth!=P.nWidth)||(Pm.nHeight!=P.nHeight)) return;
  
	for (i=0;i<P.nHeight;i++) {
		bufm=(BYTE*) pImgm->GetPixelAddress(0,i);
		bufn=(BYTE*) pImgn->GetPixelAddress(0,i);
		if (P.nBitCount==8) {
			for (j=0;j<P.nWidth;j++) {
				if (bufm[j]) bufn[j]=bufm[j];
			}
		}
		else {
			for (j=0;j<P.nWidth;j++) {
				if (bufm[j]) {
					for (k=0;k<P.nBytesPerPixel;k++)
						bufn[j*P.nBytesPerPixel+k]=bufm[j];
				}
			}
		}
	}
}

#endif  //!_INC_IPROCESSEC
 	
