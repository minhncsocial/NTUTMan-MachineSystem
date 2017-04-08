/// \file   person.h
/// \author minhnc
/// \brief  An example of Pimpl-Monostate.

#include <string>
#include <boost\shared_ptr.hpp>
class PersonImpl;
class Person 
{
public: 
	explicit Person(const std::string &name);

	std::string GetName() const;
	int GetAge() const;

	void SetName(const std::string &name);
	void SetAge(const std::string &name);

	void MakeUnique();

private:
	boost::shared_ptr<PersonImpl> mImpl;
	//std::tr1::shared_ptr<PersonImpl> mImpl;
};