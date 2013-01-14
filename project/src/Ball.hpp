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

	bool pre_collision(Body &other);
	bool post_collision(Contact &contact);
	void draw(QPainter& painter) const;

	void setState(BallState* state);
};

class BallFactory
{
public:
	static Ball* makeNormalBall(const Point &initial_position, const Vector &initial_velocity);
	static Ball* makeFireBall(const Point &initial_position, const Vector &initial_velocity);
	static Ball* makePhantomBall(const Point &initial_position, const Vector &initial_velocity);
};