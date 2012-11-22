#pragma once

#include "Body.hpp"

class Box : public virtual Body
{
	double width;
	double height;

public:
	Box(const Point &initial_position, const double &width, const double &height)
		: Body(initial_position), width(width), height(height)
	{
	}
};