#include "../Contact.hpp"

bool Contact::operator () () const
{
	return this->points.size() != 0;
}