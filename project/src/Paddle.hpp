#pragma once

#include "Box.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"

class Paddle : public Box, public Movable
{
	static const double INITIAL_WIDTH; 
	static const double INITIAL_HEIGHT;
	static const double DENSITY;

public:
	Paddle(const Point &initial_position, const Vector &initial_velocity)
		: Box(Paddle::INITIAL_WIDTH, Paddle::INITIAL_HEIGHT), Movable(initial_velocity)
	{
		this->init(Paddle::DENSITY, initial_position);
	}

	virtual ~Paddle() { };

	virtual void on_collision(Body &other, Contact &contact);
};