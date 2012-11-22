#pragma once

#include "Circle.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"

class Ball : public Circle, public Movable
{
	const double BASE_RADIUS = 10.0;

public:
	Ball(const Point &initial_position, const Vector &initial_velocity)
		: Circle(initial_position, Ball::BASE_RADIUS), Movable(initial_velocity)
	{
	}

	virtual void on_collision(Body &other, Contact &contact);
};