//   IProcessF.h

#pragma once

#ifndef		_INC_IPROCESSFH
#define		_INC_IPROCESSFH

void  AdjustAreaType(CImage *pImg);
void  ContourTracking(CImage *pImg);
void  LineCode(CImage *pImg);
void  LimitErosion(CImage *pImg);
void  ConditionDilation(CImage *pImgn,CImage *pImgm);
int   SearchAreaKernel(CImage *pImg);
int   ParamentMeasure(CImage *pImg,CPoint point,int flag,int *per,double *fac);
void  MakeMask(int x,int y,int flag);
void  CreateMaskImage(CImage *pImg);

#endif		//!_INC_IPROCESSFH
