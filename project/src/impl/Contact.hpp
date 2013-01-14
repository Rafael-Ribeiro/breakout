#include "../Contact.hpp"

Contact::Contact(const double& toc, const Vector& normal,  Body* const & body_a, Body* const & body_b)
	: _toc(toc), _normal(normal), _body_a(body_a), _body_b(body_b)
{
}

const Vector& Contact::normal() const
{
	return this->_normal;
}

const double& Contact::toc() const
{
	return this->_toc;
}

Body* const & Contact::body_a() const
{
	return this->_body_a;
}

Body* const & Contact::body_b() const
{
	return this->_body_b;
}

Contact::operator bool () const
{
	return this->_normal != Vector(0, 0);
}

bool Contact::operator > (const Contact& other) const
{
	return this->_toc > other._toc;
}