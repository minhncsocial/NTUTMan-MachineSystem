// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLLLIB01_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLLLIB01_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLLLIB01_EXPORTS
#define DLLLIB01_API __declspec(dllexport)
#else
#define DLLLIB01_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

// This class is exported from the DLLLib01.dll
class DLLLIB01_API CDLLLib01 {
public:
	CDLLLib01(void);
	// TODO: add your methods here.
};

extern DLLLIB01_API int nDLLLib01;

DLLLIB01_API int __cdecl fnDLLLib01(int a, int b);

DLLLIB01_API LONG_PTR __cdecl CreateCImage();
//__declspec(dllexport) LONG_PTR __cdecl CreateCImage();
DLLLIB01_API bool __cdecl DestroyCImage(LONG_PTR CImg);
DLLLIB01_API bool __cdecl LoadBMP(LONG_PTR CImg, char * filename);
DLLLIB01_API bool __cdecl SaveBMP(LONG_PTR CImg, char * filename);
DLLLIB01_API HBITMAP* __cdecl GetBitmap(LONG_PTR CImg);
DLLLIB01_API HBITMAP* __cdecl Threshold(LONG_PTR CImg);

#ifdef __cplusplus
}
#endif