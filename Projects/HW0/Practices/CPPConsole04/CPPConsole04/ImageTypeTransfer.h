//   ImageTransfer.h
#include "stdafx.h"

#pragma once

#ifndef		_INC_TRANSH
#define		_INC_TRANSH

void Trans1To8(BYTE *sc,BYTE *buf,int BytesPerLine);
void Trans8To1(BYTE *sc,BYTE *buf,int Width);
void Trans4cTo8(BYTE *sc,BYTE *buf,int BytesPerLine);
void Trans8To4c(BYTE *sc,BYTE *buf,int Width);
void Trans4pTo8(BYTE *sc,BYTE *buf,int BytesPerLine);
void Trans8To4p(BYTE *sc,BYTE *buf,int BytesPerLine);
void Trans4pTo4c(BYTE *sc,BYTE *buf,int BytesPerLine,int bpl);
void Trans4cTo4p(BYTE *sc,BYTE *buf,int BytesPerLine,int bpl);
void Trans24To32(BYTE *sc,BYTE *buf,int Width);
void Trans32To24(BYTE *sc,BYTE *buf,int Width);
void BmpToVga(BYTE *VgaPal,RGBQUAD *bgr,int n);
void VgaToBmp(RGBQUAD *bgr,BYTE *VgaPal,int n);
 
#endif  //!_INC_TRANSH
