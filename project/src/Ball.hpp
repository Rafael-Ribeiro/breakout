#pragma once

#include <QPainter>

#include "Circle.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Drawable.hpp"
#include "BallState.hpp"

class BallFactory; // forward declaration (used "too soon")

class Ball : public Circle, public Movable, public Drawable
{
	BallState* state;

	friend BallFactory;

protected:
	Ball(const Point &initial_position, const Vector &initial_velocity);
	void set_state(BallState* state);

public:
	static const double BASE_RADIUS;
	static const double BASE_VELOCITY;

	virtual ~Ball();

	BallState const * get_state() const;

	void draw(QPainter& painter) const;
};

class BallFactory
{
public:
	static Ball* makeNormalBall(const Point &initial_position, const Vector &initial_velocity);
	static Ball* makeFireBall(const Point &initial_position, const Vector &initial_velocity);
	static Ball* makePhantomBall(const Point &initial_position, const Vector &initial_velocity);
};