#pragma once

#include "Body.hpp"

class Circle : public virtual Body
{
	double _radius;

protected:
	Circle(const double &radius)
		: _radius(radius)
	{
	}

public:
	virtual ~Circle() {};

	double& radius();
	const double& radius() const;
};