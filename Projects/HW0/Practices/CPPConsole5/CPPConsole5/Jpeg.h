// Jpeg.h: interface for the CJpeg class.
//
//////////////////////////////////////////////////////////////////////

#ifndef		_INC_JPEG
#define		_INC_JPEG
 
////////////////////////////////////////////////////////////////
// read a JPEG file to an RGB buffer - 3 bytes per pixel
// returns a ptr to a buffer .
BYTE* ReadJPEGFile(LPCSTR lpstrFileName, UINT *uWidth, UINT *uHeight);
////////////////////////////////////////////////////////////////

// write a JPEG file from a 3-component, 1-byte per component buffer
BOOL WriteJPEGFile(LPCTSTR lpstrFileName,	// path
				   BYTE *dataBuf,			// RGB buffer
				   UINT width,				// pixels
				   UINT height,				// rows
				   BOOL color,				// TRUE = RGB
											// FALSE = Grayscale
   				   int quality);			// 0 - 100

void FreeBuffer(BYTE *Buffer);

// store a scanline to our data buffer
void j_putRGBScanline(BYTE *jpegline, 
						 int widthPix,
						 BYTE *outBuf,
						 int row);

void j_putGrayScanlineToRGB(BYTE *jpegline, 
						 int widthPix,
						 BYTE *outBuf,
						 int row);

#endif  //!_INC_JPEG
