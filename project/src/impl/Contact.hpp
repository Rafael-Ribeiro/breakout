#include "../Contact.hpp"

Vector& Contact::normal()
{
	return this->_normal;
}

const Vector& Contact::normal() const
{
	return this->_normal;
}

vector<Point>& Contact::points()
{
	return this->_points;
}

const vector<Point>& Contact::points() const
{
	return this->_points;
}

bool Contact::operator () () const
{
	return this->_points.size() != 0;
}