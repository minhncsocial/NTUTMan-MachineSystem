#include "StdAfx.h"
#include <iostream>
#include "AutoTimer.h"
#include <Windows.h>


namespace APIBook
{
	class AutoTimer::Impl
	{
	public:
		double GetElapsed() const
		{
			return((GetTickCount() - mStartTime) / 1e3);
		}

		std::string mName;
		DWORD mStartTime;
	};

	AutoTimer::AutoTimer(const std::string &name) : mImpl(new AutoTimer::Impl())
	{
		mImpl->mName = name;
		mImpl->mStartTime = GetTickCount();
	}

	AutoTimer::~AutoTimer(void)
	{
		std::cout << mImpl->mName << ": took " << mImpl->GetElapsed() << " secs" << std::endl;
		delete mImpl;
		mImpl = NULL;
	}
}