#pragma once

#include <QPainter>

#include "Circle.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Drawable.hpp"
#include "BallState.hpp"

class BallFactory; // forward declaration (used "too soon")
class Player;
class BreakoutWorld;
class PhantomBonus;
class FireBonus;

class Ball : public Circle, public Movable, public Drawable
{
	BallState* _state;
	Player* _last_player;

	friend BallFactory; /* access constructor */
	friend BreakoutWorld; /* access state() */
	friend PhantomBonus; /* access set_state() */
	friend FireBonus; /* access set_state() */

protected:
	Ball(const Point &initial_position, const Vector &initial_velocity);
	void set_state(BallState* state);

	BallState * const & state() const;

public:
	static const double BASE_RADIUS;
	static const double BASE_VELOCITY;

	virtual ~Ball();

	Player* const & last_player() const;

	void hit(Player& player);
	void draw(QPainter& painter) const;
};

class BallFactory
{
public:
	static Ball* makeNormalBall(const Point &initial_position, const Vector &initial_velocity);
	static Ball* makeFireBall(const Point &initial_position, const Vector &initial_velocity);
	static Ball* makePhantomBall(const Point &initial_position, const Vector &initial_velocity);
};