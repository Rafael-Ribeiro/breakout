#pragma once

#include <vector>

#include "Point.hpp"
#include "Vector.hpp"

using namespace std;

class Contact
{
	Vector _normal;
	vector<Point> _points;

public:
	Vector& normal();
	const Vector& normal() const;

	vector<Point>& points();
	const vector<Point>& points() const;

	bool operator () () const;
};