/// \file   personimpl.h
/// \author minhnc
/// \brief  An example of Pimpl-Monostate.

#include "StdAfx.h"
#include "personimpl.h"

PersonImpl::PersonImpl(const std::string &name) : mName(name) {}


std::string PersonImpl::GetName() const {
	return mName;
}

int PersonImpl::GetAge() const {
	return mAge;
}


void PersonImpl::SetName(const std::string &name) 
{
	mName = name;
}

void PersonImpl::SetAge(const int &age) 
{
	mAge = age;
}