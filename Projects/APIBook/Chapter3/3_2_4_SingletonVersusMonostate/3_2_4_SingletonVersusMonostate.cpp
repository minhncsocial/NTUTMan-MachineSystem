// 3_2_4_SingletonVersusMonostate.cpp : Defines the entry point for the console application.
/// \file   main
/// \author minhnc
/// \brief  An example of Pimpl-Monostate.
/// \notice because using boost::shared_ptr => add external lib
/// \notice how to add external lib: Configuration Properties/VC++ Directories/Include Directories: add directory (such as: E:\PROGRAMS\NTUT_Man Machine System\Projects\external;$(IncludePath))

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string>
#include "Monostate.h"
#include "person.h"

#define TEST_RECTANGLE		1
#define TEST_TEMPERATURE	2
#define TEST_PERSON			3
#define TEST_OPTION			TEST_PERSON

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Chapter 3_2_4" << endl;
#if TEST_OPTION == TEST_RECTANGLE
	Rectangle size;
	cout<< "height: " << size.GetHeight() << endl << " width: " << size.GetWidth() << endl;
	size.SetHeight(100);
	size.SetWidth(200);
	cout<< "height: " << size.GetHeight() << endl << " width: " << size.GetWidth() << endl;
#elif TEST_OPTION == TEST_TEMPERATURE
	Temperature temperature;
	cout<< "Temperature: " << temperature.GetTemperature() << endl;
	temperature.SetTemperature(100);
	cout<< "Temperature: " << temperature.GetTemperature() << endl;
#elif TEST_OPTION == TEST_PERSON
	Person p("Peter");
	Person pc(p);
	Person m("MINH");
	cout << "p.name(): " << p.GetName() << endl;	cout << "p.name(): " << p.GetName() << endl;	cout << "m.name(): " << m.GetName() << endl;
	string mName = "MEOMEO";
	pc.SetName("Hans");	cout << "pc.setName(\"Hans\");" << endl;	cout << "p.name(): " << p.GetName() << endl;
	cout << "pc.name(): " << pc.GetName() << endl;
#endif

	_getch();
	return 0;
}