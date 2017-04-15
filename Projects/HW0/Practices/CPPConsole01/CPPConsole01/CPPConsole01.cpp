// CPPConsole01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "DLLLib01.h"
#include "IProcessing_Pimpl.h"

using namespace std;

LONG_PTR cImg = CreateCImage();
HBITMAP * hBitmap;

LONG_PTR mImg1 = CreatemImage();

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "HELLO! This is console program testing lib" << endl;

	//int a = 30, b = 20;
	//int c = fnDLLLib01(a, b);

	//cout << "result : " << c << endl;

	//BOOLEAN _flag = LoadBMP(cImg, "D:/Test/fruits3.bmp");

	//if (_flag) 
	//{
	//	hBitmap = GetBitmap(cImg);
	//}



	_getch();
	return 0;
}

