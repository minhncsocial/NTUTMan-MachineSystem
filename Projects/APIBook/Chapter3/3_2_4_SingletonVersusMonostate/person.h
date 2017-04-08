/// \file   person.h
/// \author minhnc
/// \brief  An example of Pimpl-Monostate.
/// \notice because using boost::shared_ptr => add external lib
/// \notice how to add external lib: Configuration Properties/VC++ Directories/Include Directories: add directory (such as: E:\PROGRAMS\NTUT_Man Machine System\Projects\external;$(IncludePath))

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