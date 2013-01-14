#pragma once

#include <QPainter>

#include "Box.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Drawable.hpp"

class Paddle : public Box, public Movable, public Drawable
{
	static const double INITIAL_WIDTH; 
	static const double INITIAL_HEIGHT;

public:
	Paddle(const Point &initial_position, const Vector &initial_velocity)
		: Box(Paddle::INITIAL_WIDTH, Paddle::INITIAL_HEIGHT), Movable(initial_velocity)
	{
		this->init(initial_position);
	}

	virtual ~Paddle() { };

	void draw(QPainter& painter) const;

	virtual bool pre_collision(Body &other);
	virtual bool post_collision(Contact &contact);
};