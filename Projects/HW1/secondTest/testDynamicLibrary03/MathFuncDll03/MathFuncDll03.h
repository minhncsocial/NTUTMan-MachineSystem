// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MATHFUNCDLL03_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MATHFUNCDLL03_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MATHFUNCDLL03_EXPORTS
#define MATHFUNCDLL03_API __declspec(dllexport)
#else
#define MATHFUNCDLL03_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

// This class is exported from the MathFuncDll03.dll
class MATHFUNCDLL03_API CMathFuncDll03 {
public:
	CMathFuncDll03(void);
	// TODO: add your methods here.
};

extern MATHFUNCDLL03_API int nMathFuncDll03;

MATHFUNCDLL03_API int fnMathFuncDll03(void);

namespace MathFunc
{
	MATHFUNCDLL03_API double Add(double a, double b);
	MATHFUNCDLL03_API double Subtract(double a, double b);
	MATHFUNCDLL03_API double Multiply(double a, double b);
	MATHFUNCDLL03_API double Divide(double a, double b);
}

#ifdef __cplusplus
}
#endif