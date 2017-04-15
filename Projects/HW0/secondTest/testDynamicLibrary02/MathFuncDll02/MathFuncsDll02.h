#pragma once
//class MathFuncsDll02
//{
//public:
//	MathFuncsDll02(void);
//	~MathFuncsDll02(void);
//};

#ifdef MATHFUNCDLL02_EXPORTS
#define MATHFUNCDLL02_API __declspec(dllexport)
#else
#define MATHFUNCDLL02_API __declspec(dllimport)
#endif

#include <stdexcept>
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

namespace MathFunc
{
	__declspec(dllexport) double Add(double a, double b);
	__declspec(dllexport) double Subtract(double a, double b);
	__declspec(dllexport) double Multiply(double a, double b);
	__declspec(dllexport) double Divide(double a, double b);
}

#ifdef __cplusplus
}
#endif