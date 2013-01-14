#pragma once

#include "Body.hpp"

class Box : public virtual Body
{
	double _hwidth;
	double _hheight;

protected:
	Box(const double &width, const double &height)
		: _hwidth(width / 2), _hheight(height / 2)
	{
	}

public:
	virtual ~Box() {};

	double& hwidth();
	const double& hwidth() const;

	double& hheight();
	const double& hheight() const;

	double width() const;
	double height() const;

	double top() const;
	double bottom() const;
	double left() const;
	double right() const;
};