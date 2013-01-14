#pragma once

#include <QPainter>

#include "Circle.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Drawable.hpp"
#include "BallState.hpp"

class Ball : public Circle, public Movable, public Drawable
{
	static const double BASE_RADIUS;

	BallState* state;

public:
	Ball(const Point &initial_position, const Vector &initial_velocity);
	virtual ~Ball();

	void set_state(BallState* state);
	BallState const *  get_state() const;

	void draw(QPainter& painter) const;
};

class BallFactory
{
public:
	static Ball* makeNormalBall(const Point &initial_position, const Vector &initial_velocity);
	static Ball* makeFireBall(const Point &initial_position, const Vector &initial_velocity);
	static Ball* makePhantomBall(const Point &initial_position, const Vector &initial_velocity);
};