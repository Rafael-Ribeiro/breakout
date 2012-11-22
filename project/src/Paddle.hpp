#pragma once

#include "Box.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"

class Paddle : public Box, public Movable
{
	const double INITIAL_WIDTH = 50.0;
	const double INITIAL_HEIGHT = 10.0;

public:
	Paddle(const Point &initial_position, const Vector &initial_velocity)
		: Box(initial_position, Paddle::INITIAL_WIDTH, Paddle::INITIAL_HEIGHT), Movable(initial_velocity)
	{
	}

	virtual void on_collision(Body &other, Contact &contact);
};