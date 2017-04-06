#include "AutoTimer01.h"
#include <iostream>
#include <Windows.h>

AutoTimer01::AutoTimer01(const std::string &name)
{
	mStartTime = GetTickCount();
}


AutoTimer01::~AutoTimer01(void)
{
	std::cout << mName << ": took" << GetElapsed() << " secs" << std::endl;
}

double AutoTimer01::GetElapsed() const
{
	return (GetTickCount() - mStartTime)/1e3;
}