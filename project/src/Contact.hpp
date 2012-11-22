#pragma once

#include <vector>

#include "Point.hpp"
#include "Vector.hpp"

using namespace std;

class Contact
{
	vector<Point> points;
	Vector normal;

	bool operator () () const;
};