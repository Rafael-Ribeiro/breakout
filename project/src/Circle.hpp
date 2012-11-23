#pragma once

#include "Body.hpp"

class Circle : public virtual Body
{
	double _radius;

public:
	Circle(const Point &initial_position, const double &radius)
		: Body(initial_position), _radius(radius)
	{	
	}

	double& radius();
	const double& radius() const;
};