/// \file   person.cpp
/// \author minhnc
/// \brief  An example of Pimpl-Monostate.

#include "StdAfx.h"
#include "person.h"
#include "personimpl.h"

Person::Person(const std::string &name) : mImpl(new PersonImpl(name))
{
}

std::string Person::GetName() const
{
	return mImpl->GetName();
}

void Person::SetName(const std::string &name) 
{
	//MakeUnique();
	mImpl->SetName(name);
}

void Person::MakeUnique()
{
	if (!mImpl.unique()) 
	{
		boost::shared_ptr<PersonImpl> np(new PersonImpl(*mImpl));
		mImpl = np;
	}
}
