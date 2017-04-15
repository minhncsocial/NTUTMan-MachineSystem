//   IProcessE.h

#pragma once

#ifndef		_INC_IPROCESSEH
#define		_INC_IPROCESSEH

void LowTypeToIndex(CImage *pImgn,CImage *pImgm);

void Morphologic(CImage *pImg0,CImage *pImg1,int n);
void GMorphologic(CImage *pImg0,CImage *pImg1,int n);
 
void ToRGB(CImage *pImgn,CImage *pImgm,int n);
void ToHSV(CImage *pImgn,CImage *pImgm,int n);
void ToYIQLAB(CImage *pImgn,CImage *pImgm,int n);
void ColorSobel(CImage *pImgn,CImage *pImgm,int n);
void RemoveBackgrond(CImage *pImgn,CImage *pImgm);
void AddImage(CImage *pImgn,CImage *pImgm);
  
#endif		//!_INC_IPROCESSEH
