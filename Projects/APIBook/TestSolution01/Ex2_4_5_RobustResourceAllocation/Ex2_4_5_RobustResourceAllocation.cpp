// Ex2_4_5_RobustResourceAllocation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <boost\shared_ptr.hpp>

using namespace std;

typedef boost::shared_ptr<class MyObject> MyObjectPtr;

//class MyObject
//{
//public:
//	static MyObjectPtr CreateInstance();
//	~MyObject();
//private:
//	MyObject();
//};
//
//MyObjectPtr MyObject::CreateInstance()
//{
//	return MyObjectPtr(new MyObject());
//}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "HELLO" << endl;

	//MyObjectPtr ptr = MyObject::CreateInstance();
	//ptr = MyObject::CreateInstance();

	_getch();
	return 0;
}

