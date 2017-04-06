#ifndef AUTOTIMER05_H
#define AUTOTIMER05_H

#pragma once
#include <string>
//#include <boost/scoped_ptr.hpp>  // boost driver???

class AutoTimer05
{
public:
	explicit AutoTimer05(const std::string &name);
	~AutoTimer05(void);

private:
	class Impl;
	//boost::coped_ptr<Impl> mImpl;
};

#endif