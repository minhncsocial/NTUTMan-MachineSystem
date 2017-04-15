//   IProcessC.h

#pragma once

#ifndef		_INC_IPROCESSCH
#define		_INC_IPROCESSCH

void  ImageInvert(CImage *pImgm);
void  ColorToMonochrom(CImage *pImgm);
void  ColorToGray(CImage *pImgn,CImage *pImgm);
void  LowTypeToIndex(CImage *pImgn,CImage *pImgm);
void  IndexToLowType(CImage *pImgn,CImage *pImgm);

void  Flip(CImage *pImgm,int n);
void  Rotate90(CImage *pImgn,CImage *pImgm,int n);
void  ImageMasaic(CImage *pImgm,int n);
void  ZoomIn(CImage *pImgn,CImage *pImgm,int n);
void  ZoomOut(CImage *pImgn,CImage *pImgm,int n);
void  ImageRotate(CImage *pImgn,CImage *pImgm,double alpha);
void  ImageScale(CImage *pImgn,CImage *pImgm,double alpha);

#endif  //!_INC_IPROCESSCH
