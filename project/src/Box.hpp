#pragma once

#include "Body.hpp"

class Box : public virtual Body
{
	double _width;
	double _height;

protected:
	Box(const double &width, const double &height)
		: _width(width), _height(height)
	{
	}

public:
	virtual ~Box() {};

	double& width();
	const double& width() const;

	double& height();
	const double& height() const;
};