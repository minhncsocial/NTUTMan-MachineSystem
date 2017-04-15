// MathFuncDll03.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MathFuncDll03.h"


// This is an example of an exported variable
MATHFUNCDLL03_API int nMathFuncDll03=0;

// This is an example of an exported function.
MATHFUNCDLL03_API int fnMathFuncDll03(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see MathFuncDll03.h for the class definition
CMathFuncDll03::CMathFuncDll03()
{
	return;
}

namespace MathFunc
{
	double Add(double a, double b)
	{
		return (a + b)*2;
	}

	double Subtract(double a, double b)
	{
		return a - b;
	}

	double Multiply(double a, double b)
	{
		return a * b;
	}

	double Divide(double a, double b)
	{
		return a / b;
	}
}