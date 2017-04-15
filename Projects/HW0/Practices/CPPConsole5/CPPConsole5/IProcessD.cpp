//   IProcessD.cpp

#include "stdafx.h"
     
#ifndef		_INC_IPROCESSDC
#define		_INC_IPROCESSDC

int		nDirectionNo=0;

void GrayScaleTransfor(CImage *pImgm,int n) 
{
 	struct	IMAGEPARAMENT P;
	BYTE	**list;
	long	pg[256],tab[256];
	RGBQUAD	ColorTab[256];
	int		i,T_gray[256];

 	GetImageParament(pImgm,&P);              
	Histogram(pImgm,0,0,P.nWidth,P.nHeight,pg);
	switch(n) {
		case 1:
			GT_linear(T_gray);
 			break;
		case 2:
			GT_sqrt(T_gray);
 			break;
		case 3:
			GT_log(T_gray);
 			break;
		case 4:
			GT_square(T_gray);
 			break;
		case 5:
			GT_exp(T_gray);
 			break;
		case 6:
			GT_Equal(pg,T_gray);
 			break;
		case 7:
			for (i=0;i<256;i++) tab[i]=i;
			GT_histo_eq(pg,tab,T_gray);
 			break;
		case 8:
			GT_nega(T_gray);
 			break;
		case 9:
			Border_Equal(pg,T_gray);
 			break;
		case 10:
            DensitySegment(ColorTab);
			SetAllPalette(pImgm,ColorTab);
 			break;
		case 11:
			PsendoColor(ColorTab);
			SetAllPalette(pImgm,ColorTab);
  			break;
	}
 	if (n<10) {
		list=(BYTE**) Create2DList(pImgm);
		GT(list,P.nWidth,P.nHeight,T_gray);
		Release2DList(list);
	}
}

void Threshold(CImage *pImgm,int n,double ff)
{
 	struct	IMAGEPARAMENT P;
	BYTE	**list,*lpBuf;
	RGBQUAD	ColorTab[256];
	long	pg[256];
 	int		t,x,y,thre;
	int		tab[256],buf[20],bn;
    
 	GetImageParament(pImgm,&P);              

	list=(BYTE**) Create2DList(pImgm);
	histog(list,pg,0,0,P.nWidth,P.nHeight);
 
	switch(n) {
		case 1:
			thre=FormAnalysis(pg,tab,buf,&bn);
 			break;
		case 2:
			t=GrayImageType(pg);
			if (t==1) ff=1.0-ff;
			thre=Ptile(pg,ff);
			break;
		case 3:
			thre=Otsu(pg);
			break;
		case 4:
			thre=Minimum(pg);
			break;
		case 5:
			thre=KSW_Entropic(pg);
			break;
		case 6:
			thre=BiasNormal(pg);
			break;
		case 7:
			thre=Moment(pg);
			break;
		case 8:
			thre=ColligationThreshold(pg);
			break;
		case 9:
			thre=SimpleThreshold(pg);
			break;
	}

 	for (y=0;y<P.nHeight;y++) {
		lpBuf=(BYTE*) pImgm->GetPixelAddress(0,y);
		for (x=0;x<P.nWidth;x++,lpBuf++) {
			if (*lpBuf>=thre) *lpBuf=1;
			else		      *lpBuf=0;
		}
	}
 	memset(ColorTab,0,1024);
	SetAllPalette(pImgm,ColorTab);
    SetPalette(pImgm,1,255,255,255);

	Release2DList(list);
}

void ExpandImage(CImage *pImgn,CImage *pImgm)
{
 	struct	IMAGEPARAMENT P;
	BYTE	*buf,*buf1;
  	int		k;
 
 	GetImageParament(pImgm,&P);                           
	pImgn->Create(P.nWidth+2,P.nHeight+2,P.nBitCount,0);

	for (int i=0;i<P.nHeight;i++) {
		buf  = (BYTE*) pImgm->GetPixelAddress(0,i);       
		buf1 = (BYTE*) pImgn->GetPixelAddress(1,i+1);
  		memcpy(buf1, buf, P.nBytesPerLine);                         
	}
	buf  = (BYTE*) pImgm->GetPixelAddress(0,0); 
	buf1 = (BYTE*) pImgn->GetPixelAddress(1,0);
  	memcpy(buf1, buf, P.nBytesPerLine);
	buf  = (BYTE*) pImgm->GetPixelAddress(0,P.nHeight-1);
	buf1 = (BYTE*) pImgn->GetPixelAddress(1,P.nHeight+1);
  	memcpy(buf1, buf, P.nBytesPerLine);
	buf=(BYTE*) malloc(P.nHeight);
	GetRectValue(pImgm,0,0,1,P.nHeight,buf);
	SetRectValue(pImgn,0,1,1,P.nHeight,buf);
	GetRectValue(pImgm,P.nWidth-1,0,1,P.nHeight,buf);
	SetRectValue(pImgn,P.nWidth+1,1,1,P.nHeight,buf);
	k=GetPixelValue(pImgm,0,0);
	SetPixelValue(pImgn,0,0,k);
	k=GetPixelValue(pImgm,P.nWidth-1,0);
	SetPixelValue(pImgn,P.nWidth+1,0,k);
	k=GetPixelValue(pImgm,0,P.nHeight-1);
	SetPixelValue(pImgn,0,P.nHeight+1,k);
	k=GetPixelValue(pImgm,P.nWidth-1,P.nHeight-1);
	SetPixelValue(pImgn,P.nWidth+1,P.nHeight+1,k);
	free(buf);
}

void ReduceImage(CImage *pImgn,CImage *pImgm)
{
 	struct	IMAGEPARAMENT P;
	BYTE	*buf,*buf0;
  
 	GetImageParament(pImgn,&P);                           
	for (int i=0;i<P.nHeight;i++) {
		buf0 = (BYTE*) pImgm->GetPixelAddress(1,i+1);
		buf  = (BYTE*) pImgn->GetPixelAddress(0,i);       
  		memcpy(buf, buf0, P.nBytesPerLine);                         
	}
}

void LocalProcess(CImage *pImg,int n)
{
 	struct	IMAGEPARAMENT P;
	BYTE	**list1,**list0;
	RGBQUAD	ColorTab[256];
 	CImage  gImg1,gImg0;

  	ExpandImage(&gImg1,pImg);
 	GetImageParament(&gImg1,&P);
	gImg0.Create(P.nWidth,P.nHeight,P.nBitCount,0);
	ImageCopy(&gImg0,&gImg1);
	list1=(BYTE**) Create2DList(&gImg1);
	list0=(BYTE**) Create2DList(&gImg0);
 
 	GetImageParament(&gImg1,&P); 
    switch(n) {
		case 1:
			Gradiant(list0,list1,P.nWidth,P.nHeight);
			break;
		case 2:
			Roberts(list0,list1,P.nWidth,P.nHeight);
			break;
		case 3:
			Sobel(list0,list1,P.nWidth,P.nHeight);
			break;
		case 4:
			Laplacian(list0,list1,P.nWidth,P.nHeight);
			break;
		case 5:
			Kirsch(list0,list1,P.nWidth,P.nHeight,nDirectionNo);
			break;
		case 6:
			Robinson(list0,list1,P.nWidth,P.nHeight,nDirectionNo);
			break;
		case 7:
			Prewitt(list0,list1,P.nWidth,P.nHeight,nDirectionNo);
			break;
		case 8:
			Smooth5(list0,list1,P.nWidth,P.nHeight);
			break;
		case 9:
			Smooth9(list0,list1,P.nWidth,P.nHeight);
			break;
		case 10:
			Median5(list0,list1,P.nWidth,P.nHeight);
			break;
		case 11:
			Median9(list0,list1,P.nWidth,P.nHeight);
			break;
		case 12:
			BoundEnhance(list0,list1,P.nWidth,P.nHeight);
			break;
		case 13:
			LapSketch(list0,list1,P.nWidth,P.nHeight);
			break;
		case 14:
			LoG(list0,list1,P.nWidth,P.nHeight);
			break;
		case 15:
			OnePWidthW(list0,list1,P.nWidth,P.nHeight);
			break;
		case 16:
			RemoveLineNoise(list0,list1,P.nWidth,P.nHeight);
			break;
		case 17:
			SobelThin(list0,list1,P.nWidth,P.nHeight);
			break;
		case 18:
			LogPrewitt(list0,list1,P.nWidth,P.nHeight,0.5);
			break;
	}
 
	Release2DList(list1);
	Release2DList(list0);

	ReduceImage(pImg,&gImg0);
	if (n==18) {
		memset(ColorTab,0,1024);
		SetAllPalette(pImg,ColorTab);
		SetPalette(pImg,1,255,255,255);
	}

	gImg1.Destroy();
	gImg0.Destroy();
}

void CurveThinning(CImage *pImg0,CImage *pImg1,int n)
{
 	struct	IMAGEPARAMENT P;
	BYTE	**list;
      
	LowTypeToIndex(pImg0,pImg1);
	SetPalette(pImg0,0,0,0,0);
    SetPalette(pImg0,1,255,255,255);
   
 	GetImageParament(pImg0,&P);
	list=(BYTE**) Create2DList(pImg0);
	switch(n) {
		case 1:
			Hilditch(list,P.nBytesPerLine,P.nHeight);
			break;
		case 2:
			Deutch(list,P.nBytesPerLine,P.nHeight);
			break;
		case 3:
			FastThin(list,P.nBytesPerLine,P.nHeight);
			break;
		case 4:
			Naccache(list,P.nBytesPerLine,P.nHeight);
			break;
		case 5:
			Pavlidis1(list,P.nBytesPerLine,P.nHeight);
			break;
		case 6:
			Pavlidis2(list,P.nBytesPerLine,P.nHeight);
			break;
		case 7:
			Rosenfeld4(list,P.nBytesPerLine,P.nHeight);
			break;
		case 8:
			Rosenfeld8(list,P.nBytesPerLine,P.nHeight);
			break;
		case 9:
			RemoveNoise(list,P.nBytesPerLine,P.nHeight);
			break;
	}

	Release2DList(list);
}

void Distancing(CImage *pImg)
{
 	struct	IMAGEPARAMENT P;
	BYTE	**list;
	int		k;
 	CImage  gImg0;
  
	k=ImageType(pImg);
 	if (k==2)
		Threshold(pImg,1,0);
	else if(k!=0) return;
 
 	ExpandImage(&gImg0,pImg);
 
	GetImageParament(&gImg0,&P);
	DrawBox(&gImg0,0,0,P.nWidth,P.nHeight,1,255);
	list=(BYTE**) Create2DList(&gImg0);
 	Distance(list,P.nWidth,P.nHeight);
	Release2DList(list);
 
  	ReduceImage(pImg,&gImg0);
 	gImg0.Destroy();
}

void Projection(CImage *pImg,int* Tab,int flag)
{
 	struct	IMAGEPARAMENT P;
	int		i,j;
	BYTE	*buf;

	GetImageParament(pImg,&P);
    if (flag==0)
	{
		for (i=0;i<P.nHeight;i++) Tab[i]=0;
		for (i=0;i<P.nHeight;i++) {
			buf=(BYTE*) pImg->GetPixelAddress(0,i);
			for (j=0;j<P.nWidth;j++) Tab[i]+=buf[j];
			Tab[i]/=P.nWidth;
		}
 	}
	else
	{
		for (i=0;i<P.nWidth;i++) Tab[i]=0;
		buf=(BYTE*)malloc(P.nHeight);
		for (i=0;i<P.nWidth;i++) {
			GetRectValue(pImg,i,0,1,P.nHeight,buf);
			for (j=0;j<P.nHeight;j++) Tab[i]+=buf[j];
			Tab[i]/=P.nHeight;
		}
		free(buf);
 	}
}

void Histogram(CImage *pImg,int x,int y,int Dx,int Dy,long *pg)
{
 	struct	IMAGEPARAMENT P;
	int		i,j;
	BYTE	*buf;

	GetImageParament(pImg,&P);
  	for (i=0;i<256;i++)  pg[i]=0;
	for(i=y;i<y+Dy;i++) 
	{
		buf=(BYTE*) pImg->GetPixelAddress(0,i);
 		for (j=x;j<x+Dx;j++) pg[buf[j]]++;	
	}
}

void CreateProjection(CImage *pImg,int *Tab,int n,int flag)
{
	CDC		*pDC;
  	int		x,y,m,i,k,d=20;
   
	for (i=0,k=0;i<n;i++) k+=Tab[i];
	k/=n;
  	if (flag==0)
	{
		x=256;		y=n;
	}
	else
	{
		x=n;		y=256;
	}
 	pImg->Destroy();
	pImg->Create(x+2,y+2,24,0);
	RectFillValue(pImg,0,0,x+2,y+2,0xffffff);
 
    m=4;
	pDC = CDC::FromHandle(pImg->GetDC());
 	if (flag==0)
	{
 		pDC->MoveTo(d,0);
		pDC->LineTo(d,n);
		pDC->MoveTo(d+Tab[m],m);
		for(i=m;i<n-m;i++)
			pDC->LineTo(d+Tab[i],i);
	}
	else
	{
 		pDC->MoveTo(0,d);
		pDC->LineTo(n,d);
		pDC->MoveTo(m,d+Tab[m]);
		for(i=m;i<n-m;i++)
			pDC->LineTo(i,d+Tab[i]);
	}
 	pImg->ReleaseDC();
}

void CreateHistogram(CImage *pImg,long *pg,int h,int flag,int t)
{
	CDC		*pDC;
	long	k,m,n,x,y;
 	int		i;
   
	x=10;
	y=h+10;
	pImg->Destroy();
	pImg->Create(256+20,y+10,24,0);
	RectFillValue(pImg,0,0,276,h+20,0xffffff);
 
	m=SearchScale(pg,2);
	k=m/h+1;

	pDC = CDC::FromHandle(pImg->GetDC());
  	pDC->MoveTo(x,y);
	pDC->LineTo(x+256,y);
 	pDC->MoveTo(x,y-pg[0]/k);
	for(i=0;i<256;i++) 
	{
		if (flag==0)
			pDC->MoveTo(x+i,y);
		n=pg[i]/k;
		if (n>h) n=h;
		pDC->LineTo(x+i,y-n);
	}
	if (t>0) {
		t=(256-t);
 		pDC->MoveTo(x+t,y+2);
		pDC->LineTo(x+t,y+12);
	}
	pImg->ReleaseDC();
}

void CreateColorStrip(CImage *pImgn,CImage *pImgm,int Dx,int Dy)
{
	RGBQUAD	ColorTab[256];
	BYTE	buf[2048];
	int		i,k;

	pImgn->Destroy();
	pImgn->Create(Dx+2,Dy+2,8,0);
	GetAllPalette(pImgm,ColorTab);
	SetAllPalette(pImgn,ColorTab);

	k=Dx/256;
	if (k==0)  return;
	Dx=256*k;
	for (i=0;i<Dx;i++) buf[i]=i/k;
	for (i=0;i<Dy;i++) 
		SetRectValue(pImgn,1,1+i,Dx,1,buf);
	DrawBox(pImgn,0,0,Dx+2,Dy+2,1,0);
}

void CreateTransferCurve(CImage *pImg,long *pg,int f)    
{
	CDC		*pDC;
  	CPen	penRed(PS_SOLID,1,RGB(255,0,0)),
		    penGreen(PS_SOLID,1,RGB(0,255,0)),
		    penBlue(PS_SOLID,1,RGB(0,0,255)), *pOldPen=NULL;
	int		i,T_gray[256];
	long	tab[256];
	RGBQUAD	ColorTab[256];
  	BYTE	*buf;
  

 	switch(f) {
		case 1:
			GT_linear(T_gray);
 			break;
		case 2:
			GT_sqrt(T_gray);
 			break;
		case 3:
			GT_log(T_gray);
 			break;
		case 4:
			GT_square(T_gray);
 			break;
		case 5:
			GT_exp(T_gray);
 			break;
		case 6:
			GT_Equal(pg,T_gray);
 			break;
		case 7:
			for (i=0;i<256;i++) tab[i]=i;
			GT_histo_eq(pg,tab,T_gray);
 			break;
		case 8:
			GT_nega(T_gray);
 			break;
		case 9:
			Border_Equal(pg,T_gray);
 			break;
	} 

	pImg->Destroy();
	pImg->Create(130,130,24,0);
	RectFillValue(pImg,0,0,130,130,0xffffff);

	pDC = CDC::FromHandle(pImg->GetDC());
	if (f<10)
	{
		pDC->MoveTo(0,0);
		pDC->LineTo(0,128);
 		pDC->MoveTo(0,128);
		pDC->LineTo(128,128);
  		pDC->MoveTo(0,128-T_gray[1]/2);
		for (i=3;i<256;i+=2) 
 			pDC->LineTo(i/2,128-T_gray[i]/2);
	}
	else if (f==11)
	{
		PsendoColor(ColorTab);

 		pDC->MoveTo(0,0);
		pDC->LineTo(0,128);
 		pDC->MoveTo(0,128);
		pDC->LineTo(128,128);

		buf=(BYTE*) ColorTab;
		pOldPen = pDC->SelectObject(&penBlue);
		pDC->MoveTo(0,128-buf[0]/2);
		for (i=3;i<256;i+=2) 
 			pDC->LineTo(i/2,128-buf[4*i]/2);

		pDC->SelectObject(&penGreen);
		pDC->MoveTo(0,128-buf[1]/2);
		for (i=3;i<256;i+=2) 
 			pDC->LineTo(i/2,128-buf[4*i+1]/2);

		pDC->SelectObject(&penRed);
 		pDC->MoveTo(0,128-buf[2]/2);
		for (i=3;i<256;i+=2) 
 			pDC->LineTo(i/2,128-buf[4*i+2]/2);

		pDC->SelectObject(pOldPen);
		penRed.DeleteObject();
		penGreen.DeleteObject();
		penBlue.DeleteObject();
	}
	pImg->ReleaseDC();
}

void CreateHistogramA(CImage *pImg,CImage *pImg1,int h,int flag)
{
	struct	IMAGEPARAMENT P;
 	long	pg[256];
 	int		i,j,x,y;
	int		thre,tab[256],buf[20];
	CDC		*pDC;
  	CPen	penRed(PS_SOLID,1,RGB(255,0,0)),
		    penGreen(PS_SOLID,1,RGB(0,255,0)),
		    penBlue(PS_SOLID,1,RGB(0,0,255)), *pOldPen=NULL;
	char	Text[20];
  	char	*textbuf[]={"",
		                "单峰直方图",
	                    "双峰直方图",
	                    "多峰直方图" };
  
	GetImageParament(pImg1,&P);
 	Histogram(pImg1,0,0,P.nWidth,P.nHeight,pg);
	thre=FormAnalysis(pg,tab,buf,&j);

	x=10;
	y=h+40;
	pImg->Destroy();
	pImg->Create(256+20,y+20,24,0);
	RectFillValue(pImg,0,0,276,h+50,0xffffff);
 
	pDC = CDC::FromHandle(pImg->GetDC());
 	pDC->MoveTo(x,y);
	pDC->LineTo(x+256,y);

	pDC->MoveTo(x,y-tab[0]);
	for(i=0;i<256;i++) 
	{
		if (flag%2==0)
			pDC->MoveTo(x+i,y);
 		pDC->LineTo(x+i,y-tab[i]);
	}
	if (j>5)
		pDC->TextOut(90,5,textbuf[3]);
	else if (j>3)
		pDC->TextOut(90,5,textbuf[2]);
	else
		pDC->TextOut(90,5,textbuf[1]);

	pOldPen = pDC->SelectObject(&penRed);

	for (i=1;i<j-1;i+=2) {
		pDC->MoveTo(x+buf[i],y+5);
 		pDC->LineTo(x+buf[i],y-tab[buf[i]]-7);
	}

	pDC->SelectObject(&penBlue);
 	for (i=0;i<j;i+=2) {
		if ((buf[i]==0)||(buf[i]==255)) continue;
		pDC->MoveTo(x+buf[i],y+5);
 		pDC->LineTo(x+buf[i],y-tab[buf[i]]-7);
	}

	pDC->SelectObject(&penGreen);
	pDC->MoveTo(x+thre,y);
	if (flag>2) {
		pDC->LineTo(x+thre,y+10);
		sprintf(Text,"%d",thre);
		pDC->TextOut(210,5,Text);
	}

	pDC->SelectObject(pOldPen);
	penRed.DeleteObject();
	penGreen.DeleteObject();
	penBlue.DeleteObject();
 	pImg->ReleaseDC();
}

#endif  //!_INC_IPROCESSDC
 	
