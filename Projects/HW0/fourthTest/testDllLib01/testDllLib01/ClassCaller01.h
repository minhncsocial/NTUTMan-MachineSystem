#pragma once
#include "Class01.h"
#include <stdexcept>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

class CClassCaller01
{
public:
	CClassCaller01(void);
	~CClassCaller01(void);
};
extern __declspec(dllexport) CClass01* CreateClass01();
extern __declspec(dllexport) void DisposeClass01(CClass01* a_pObject);
extern __declspec(dllexport) void showNotify(CClass01* a_pObject);
extern __declspec(dllexport) double sum(CClass01* a_pObject, double varX, double varY);

extern "C" {__declspec(dllexport) double testAdd(double a, double b);}

#ifdef __cplusplus
}
#endif