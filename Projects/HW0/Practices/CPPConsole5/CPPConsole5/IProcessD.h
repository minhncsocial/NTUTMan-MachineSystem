//   IProcessD.h

#pragma once

#ifndef		_INC_IPROCESSDH
#define		_INC_IPROCESSDH

void LowTypeToIndex(CImage *pImgn,CImage *pImgm);

void ExpandImage(CImage *pImgn,CImage *pImgm);
void ReduceImage(CImage *pImgn,CImage *pImgm);

void Projection(CImage *pImg,int* Tab,int flag);
void CreateProjection(CImage *pImg,int *Tab,int n,int flag);
void Histogram(CImage *pImg,int x,int y,int Dx,int Dy,long *pg);
void CreateHistogram(CImage *pImg,long *pg,int h,int flag,int n);
void CreateHistogramA(CImage *pImg,CImage *pImg1,int h,int flag);
void CreateColorStrip(CImage *pImgn,CImage *pImgm,int Dx,int Dy);
void CreateTransferCurve(CImage *pImg,long *pg,int f);
int  ColorHistogram(CImage *pImg,int x,int y,int Dx,int Dy,long *pg,int n);
  
void GrayScaleTransfor(CImage *pImgm,int n); 
void Threshold(CImage *pImgm,int n,double ff);
void LocalProcess(CImage *pImg,int n);
void CurveThinning(CImage *pImg0,CImage *pImg1,int n);
void Distancing(CImage *pImg);
  
#endif		//!_INC_IPROCESSDH
