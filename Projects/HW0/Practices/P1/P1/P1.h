// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the P1_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// P1_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef P1_EXPORTS
#define P1_API __declspec(dllexport)
#else
#define P1_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"{
#endif
	// This class is exported from the P1.dll
	/*class P1_API CP1 {
	public:
		CP1(void);
		// TODO: add your methods here.
	};

	extern P1_API int nP1;*/

	P1_API int __cdecl fnP1(int a, int b);

	P1_API LONG_PTR __cdecl CreateCImage();
	P1_API bool __cdecl DestroyCImage(LONG_PTR CImg);
	P1_API bool __cdecl LoadBMP(LONG_PTR CImg, char* filename);
	P1_API HBITMAP* __cdecl GetBitmap(LONG_PTR CImg);

#ifdef __cplusplus
}
#endif