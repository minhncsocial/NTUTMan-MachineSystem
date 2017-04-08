#ifndef AUTOTIMER_H
#define AUTOTIMER_H

#pragma once
#include <string>

namespace APIBook 
{
	class AutoTimer
	{
	public:
		explicit AutoTimer(const std::string &name);
		~AutoTimer(void);
		
		class Impl;

	private:
		AutoTimer(const AutoTimer &);
		const AutoTimer &operator = (const AutoTimer &);
		Impl *mImpl;
	};
}

#endif