#pragma once

#include "Body.hpp"

class Circle : public virtual Body
{
	double radius;

public:
	Circle(const Point &initial_position, const double &radius)
		: Body(initial_position) , radius(radius)
	{	
	}
};