#include "AutoTimer05.h"
#include <iostream>
#include <Windows.h>

class AutoTimer05::Impl
{
public:
	double GetElapsed() const
	{
		return (GetTickCount() - mStartTime)/1e3;
	}
	
	std::string mName;
	DWORD mStartTime;

private:

};

AutoTimer05::AutoTimer05(const std::string &name) : mImpl(new AutoTimer05::Impl())
{
	mImpl->mStartTime = GetTickCount();
}


AutoTimer05::~AutoTimer05(void)
{
	std::cout << mImpl->mName << ": took" << mImpl->GetElapsed() << " secs" << std::endl;
}
