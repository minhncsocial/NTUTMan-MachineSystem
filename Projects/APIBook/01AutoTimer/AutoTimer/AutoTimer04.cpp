#include "AutoTimer04.h"
#include <iostream>
#include <Windows.h>

class AutoTimer04::Impl
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

AutoTimer04::AutoTimer04(const std::string &name) : mImpl(new AutoTimer04::Impl())
{
	mImpl->mStartTime = GetTickCount();
}


AutoTimer04::~AutoTimer04(void)
{
	std::cout << mImpl->mName << ": took" << mImpl->GetElapsed() << " secs" << std::endl;
	delete mImpl;
	mImpl = NULL;
}
