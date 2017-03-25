#include "E:\PROGRAMS\NTUT_Man Machine System\Projects\HW1\thirdTest\MyClassCpp\MyClassCpp\header.h"
#include "E:\PROGRAMS\NTUT_Man Machine System\Projects\HW1\thirdTest\MyClassCpp\MyClassCpp\body.cpp"

extern "C" __declspec(dllexport) double sumTwo(double var_x, double var_y)
{
	myClass MC(var_x, var_y);

	return MC.sumX_Y();


}