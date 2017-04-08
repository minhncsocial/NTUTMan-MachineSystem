/// \file   personimpl.cpp
/// \author minhnc
/// \brief  An example of Pimpl-Monostate.

#include <string>

class  PersonImpl 
{
public:
	explicit PersonImpl(const std::string &name);

	std::string GetName() const;
	int GetAge() const;

	void SetName(const std::string &name);
	void SetAge(const int &age);

private:
	std::string mName;
	int mAge;
};