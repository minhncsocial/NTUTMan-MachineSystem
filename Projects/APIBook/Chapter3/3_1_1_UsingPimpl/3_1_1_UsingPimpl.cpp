// 3_1_1_UsingPimpl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "AutoTimer.h"

using namespace std;

void testTime(const string &name)
{
	APIBook::AutoTimer timer1(name);
	//APIBook::AutoTimer timer2 = timer1;
	for (long i = 1; i <= 1000000000; i++);

	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "CONG MINH" << endl;
	testTime("HELLO");

	_getch();
	return 0;
}

