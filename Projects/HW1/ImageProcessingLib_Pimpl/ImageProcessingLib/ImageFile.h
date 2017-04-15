#pragma once

#ifndef		_INC_FILE
#define		_INC_FILE

#include "stdafx.h"

struct VGA_PAL {
	BYTE	red;
	BYTE	green;
	BYTE	blue;
};

#define	IMAGEWIDTH			0x100
#define	IMAGELENGTH			0x101
#define	BITSPERSAMPLE		0x102
#define	COMPRESSION			0x103
#define	PHOTOMETRICINTERP	0x106
#define	STRIPOFFSETS		0x111
#define	COLORMAP			0x140
 
struct TIF_IFH {
	char    ByteOrder[2];
	WORD    Version;
	DWORD   FirstIFD;
};

struct TIF_DE {
	WORD    Tag;
	WORD    Type;
	DWORD   Length;
	DWORD   ValOff;
};

struct PCX_HEAD {
	BYTE	Header;
	BYTE	Version;
	BYTE	Encode;
	BYTE	BitPerPixel;
	WORD	X1;
	WORD	Y1;
	WORD	X2;
	WORD	Y2;
	WORD	Hres;
	WORD	Vres;
	struct	VGA_PAL pal[16];
	BYTE	Resered1;
	BYTE	NumOfPlanes;
	WORD	BytesPerLine;
	WORD	Vmode;
	BYTE	Resered2[58];
};

struct PCX_END {
	BYTE	P_flag;
	struct	VGA_PAL pal[256];
};

struct GIF_GLOBAL {
	char	version[3];
	char	version1[3];
	WORD	screen_width;
	WORD	screen_depth;
	BYTE	global_flag;
	BYTE	back_color;
	BYTE	zero;
};

struct GIF_LOCAL {
	char	comma;
	WORD	image_left;
	WORD	image_top;
	WORD	image_wide;
	WORD	image_deep;
	BYTE	local_flag;
};

struct TGA_HEAD {
	BYTE    IdLength;
	BYTE    ColorType;
	BYTE    ImageType;
	WORD    FirstColor;
	WORD    ColorLength;
	BYTE    ColorBit;
	WORD    X0;
	WORD    Y0;
	WORD    Width;
	WORD    Height;
	BYTE    Bits;
	BYTE    AttribBit;
};

struct TGA_PAL {
	BYTE	blue;
	BYTE	green;
	BYTE	red;
};

int PaletteType(RGBQUAD	*ColorTab);

#endif  //!_INC_FILE