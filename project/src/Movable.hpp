#pragma once

#include "Body.hpp"
#include "Drawable.hpp"
#include "Vector.hpp"

class Movable : public virtual Body
{
	Vector _velocity;

protected:
	Movable(const Vector &initial_velocity)
		: Body(), _velocity(initial_velocity)
	{
	}

public:
	Vector& velocity();
	const Vector& velocity() const;
	
	void step(const double &dt);
};