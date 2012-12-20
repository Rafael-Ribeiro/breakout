#pragma once

#include "Body.hpp"
#include "Drawable.hpp"
#include "Vector.hpp"

class Movable : public virtual Body
{
	Vector _velocity;

protected:
	Movable(const Vector &initial_velocity)
		: _velocity(initial_velocity)
	{
	}

public:
	virtual ~Movable() { };

	Vector& velocity();
	const Vector& velocity() const;
	
	void step(const double &dt);
};