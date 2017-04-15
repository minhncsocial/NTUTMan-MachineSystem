//   IProcessF.cpp

#include "stdafx.h"
     
#ifndef		_INC_IPROCESSFC
#define		_INC_IPROCESSFC

extern	int	   ThreTable[256];
int		nTrackFlag=0;

void  AdjustAreaType(CImage *pImg)
{
 	struct	IMAGEPARAMENT P;
 	long	pg[256];
	int		object;

	GetImageParament(pImg,&P); 
    if (nTrackFlag==1) object=1;
 	else if (nTrackFlag==2) object=0;
 	else {
		Histogram(pImg,0,0,P.nWidth,P.nHeight,pg);
		if (pg[0]<pg[1]) object=0;
		else   object=1;
	}
	if (object==0) 
		ImageInvert(pImg);
}

void  ContourTracking(CImage *pImg)
{
 	struct	IMAGEPARAMENT P;
 	BYTE	**list;
     
	AdjustAreaType(pImg);
	for (int i=0;i<256;i++) ThreTable[i]=0;
	ThreTable[1]=1;
 	GetImageParament(pImg,&P); 
 	list=(BYTE**) Create2DList(pImg);
    MutiTrack(list,P.nBytesPerLine,P.nHeight);
	Release2DList(list);
}

void  LineCode(CImage *pImg) 
{
 	struct	IMAGEPARAMENT P;
 	BYTE	**list;
    
 	AdjustAreaType(pImg);
	GetImageParament(pImg,&P); 
 	list=(BYTE**) Create2DList(pImg);
    LineCoding(list,P.nBytesPerLine,P.nHeight);
	Release2DList(list);
}

int   SearchAreaKernel(CImage *pImg)
{
 	struct	IMAGEPARAMENT P;
 	BYTE	**list;
	int		n;
    
 	AdjustAreaType(pImg);
	GetImageParament(pImg,&P); 
 	list=(BYTE**) Create2DList(pImg);
    n=SearchKernel(list,P.nBytesPerLine,P.nHeight);
	Release2DList(list);
	return(n);
}

void  LimitErosion(CImage *pImg) 
{
 	struct	IMAGEPARAMENT P;
 	BYTE	**list;
    
 	AdjustAreaType(pImg);
	GetImageParament(pImg,&P); 
 	list=(BYTE**) Create2DList(pImg);
    LimitErosing(list,P.nBytesPerLine,P.nHeight);
	Release2DList(list);
}

void  ConditionDilation(CImage *pImgn,CImage *pImgm) 
{
 	struct	IMAGEPARAMENT Pm,P;
 	BYTE	**list,**list1;
	CImage	gImg;
      
	GetImageParament(pImgm,&Pm);
  	GetImageParament(pImgn,&P);
 	if ((Pm.nWidth!=P.nWidth)||(Pm.nHeight!=P.nHeight)) return;
 	LowTypeToIndex(&gImg,pImgn);

  	list1=(BYTE**) Create2DList(pImgm);
 	list =(BYTE**) Create2DList(&gImg);
    ConditionDilating(list,list1,Pm.nBytesPerLine,Pm.nHeight,50);
	Release2DList(list);
	Release2DList(list1);
	gImg.Destroy();
	DrawBox(pImgm,0,0,P.nWidth,P.nHeight,2,0);
}

int   ParamentMeasure(CImage *pImg,CPoint point,int flag,int *per,double *fac)
{
 	struct	IMAGEPARAMENT P;
 	BYTE	**list;
	int		ar;
     
 	GetImageParament(pImg,&P); 
 	list=(BYTE**) Create2DList(pImg);
    ar=ParaMeasure(list,P.nBytesPerLine,P.nHeight,point,flag);
	if (flag==1) {
		GetAreaParament(per,&ar,fac);
	}
 	Release2DList(list);
	return(ar);
}

void  MakeMask(int x,int y,int flag)
{
	MakingMask(x,y,flag);
}

void  CreateMaskImage(CImage *pImg)
{
 	struct	IMAGEPARAMENT P;
 	RGBQUAD ColorTab[256];
	int		x,y,Dx,Dy;
	BYTE	*buf,**list;

	GetMaskSize(&x,&y,&Dx,&Dy);
	if (!pImg->IsNull())
		pImg->Destroy();
	pImg->Create(Dx,Dy,8,0);
    memset(ColorTab,0,1024);
	SetAllPalette(pImg,ColorTab);
	SetPalette(pImg,1,255,255,255);
 	GetImageParament(pImg,&P); 
	buf=(BYTE*)pImg->GetPixelAddress(0,P.nHeight-1);
	memset(buf,0,P.nSize);

  	list=(BYTE**) Create2DList(pImg);
	GetMaskImage(list,x,y);
 	Release2DList(list);
}

#endif  //!_INC_IPROCESSFC
 	
