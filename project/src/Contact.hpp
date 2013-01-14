#pragma once

#include <vector>

#include "Point.hpp"
#include "Vector.hpp"

using namespace std;

class Body;

class Contact
{
	double _toc;
	Vector _normal;
	Body* _body_a;
	Body* _body_b;

public:
	Contact(const double& toc = 0, const Vector& normal = Vector(0,0), Body* const & body_a = NULL, Body* const & body_b = NULL);
	
	const Vector& normal() const;
	const double& toc() const;
	Body* const & body_a() const;
	Body* const & body_b() const;

	operator bool () const;
	bool operator > (const Contact& other) const;
};