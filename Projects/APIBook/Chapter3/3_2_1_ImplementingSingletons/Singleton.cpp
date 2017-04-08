#include "StdAfx.h"
#include "Singleton.h"
#include <iostream>

Singleton &Singleton::GetInstance()
{
	static Singleton instance;
	return instance;
}

Singleton::Singleton(void)
{
	std::cout << "Singleton created" << std::endl;
}


Singleton::~Singleton(void)
{
	std::cout << "Singleton destroyed" << std::endl;
}

int Singleton::GetState()
{
	return 42;
}