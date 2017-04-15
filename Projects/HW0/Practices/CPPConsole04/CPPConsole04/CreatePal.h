/******************************************************************
  CreatePal.H

  Performing Color Quantization algorithm

******************************************************************/

#ifndef		_CREATEPAL_H
#define		_CREATEPAL_H

void Create8TreePal(CImage *pImg,RGBQUAD *Pal, UINT nMaxColors, UINT nColorBits);
void TrueColorToIndex(CImage *pImg0,CImage *pImg1);

#endif		//!_CREATEPAL_H
