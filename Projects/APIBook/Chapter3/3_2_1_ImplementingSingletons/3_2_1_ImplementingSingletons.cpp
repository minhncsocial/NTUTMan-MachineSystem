// 3_2_1_ImplementingSingletons.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "GameSetting.h"
#include "Singleton.h"
#include "Monostate.h"

using namespace std;

//GameSetting *GameSetting::_instance = NULL;
//
//void someFunction()
//{
//	GameSetting *setting = GameSetting::getInstance();
//	setting->displaySetting();
//}

void doSomething(int n)
{
	Singleton &foo = Singleton::GetInstance();
	foo.GetState();
	if (n == 0) cout << "joke" << endl;
	else doSomething(n-1);
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "This is programme implementing Singleton" << endl;

	//GameSetting *setting = GameSetting::getInstance();
	//setting->displaySetting();
	//setting->setBrighness(200);
	//someFunction();
	Singleton &foo = Singleton::GetInstance();
	foo.GetState();

	//Singleton &foo2 = Singleton::GetInstance();
	//foo2.GetState();

	doSomething(3);

	Monostate state;
	cout << "Monostate: " << state.GetTheAnswer() << endl;
	
	_getch();
	return 0;
}

