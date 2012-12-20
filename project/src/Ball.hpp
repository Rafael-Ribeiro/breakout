#pragma once

#include <QPainter>

#include "Circle.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Drawable.hpp"

class Ball : public Circle, public Movable, public Drawable
{
	static const double BASE_RADIUS;
	static const double DENSITY;

public:
	Ball(const Point &initial_position, const Vector &initial_velocity)
		: Circle(Ball::BASE_RADIUS), Movable(initial_velocity), Drawable()
	{
		this->init(Ball::DENSITY, initial_position);
	}

	virtual ~Ball() {};

	virtual void on_collision(Body &other, Contact &contact);

	void draw(QPainter& painter) const;
};