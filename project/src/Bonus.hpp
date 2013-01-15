#pragma once

#include <QPainter>

#include "Box.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Drawable.hpp"
#include "Movable.hpp"

class Player;
class BreakoutWorld;

class Bonus : public Box, public Movable, public Drawable
{
public:
	static const unsigned int BASE_WIDTH;
	static const unsigned int BASE_HEIGHT;
	static const double BASE_VELOCITY;

	Bonus(const Point &initial_position, const Vector& initial_velocity);
	virtual ~Bonus();

	virtual void draw(QPainter& painter) const = 0;
	virtual void execute(BreakoutWorld& world, Player& player) = 0;
};

class SpeedBonus : public Bonus
{
public:
	SpeedBonus(const Point &initial_position, const Vector& initial_velocity);

	void draw(QPainter& painter) const;
	void execute(BreakoutWorld& world, Player& player);
};

class RadiusBonus : public Bonus
{
public:
	RadiusBonus(const Point &initial_position, const Vector& initial_velocity);

	void draw(QPainter& painter) const;
	void execute(BreakoutWorld& world, Player& player);
};

class BallBonus : public Bonus
{
public:
	BallBonus(const Point &initial_position, const Vector& initial_velocity);

	void draw(QPainter& painter) const;
	void execute(BreakoutWorld& world, Player& player);
};

class PhantomBonus : public Bonus
{
public:
	PhantomBonus(const Point &initial_position, const Vector& initial_velocity);

	void draw(QPainter& painter) const;
	void execute(BreakoutWorld& world, Player& player);
};

class FireBonus : public Bonus
{
public:
	FireBonus(const Point &initial_position, const Vector& initial_velocity);

	void draw(QPainter& painter) const;
	void execute(BreakoutWorld& world, Player& player);
};

class WidthBonus : public Bonus
{
public:
	WidthBonus(const Point &initial_position, const Vector& initial_velocity);

	void draw(QPainter& painter) const;
	void execute(BreakoutWorld& world, Player& player);
};

class BonusFactory
{
public:
	static Bonus* make_random_bonus(const Point &initial_position, const Vector& initial_velocity);

	/* adds effects to balls */
	static SpeedBonus* make_speed_bonus(const Point &initial_position, const Vector& initial_velocity);
	static RadiusBonus* make_radius_bonus(const Point &initial_position, const Vector& initial_velocity);
	static BallBonus* make_ball_bonus(const Point &initial_position, const Vector& initial_velocity);
	static PhantomBonus* make_phantom_bonus(const Point &initial_position, const Vector& initial_velocity);
	static FireBonus* make_fire_bonus(const Point &initial_position, const Vector& initial_velocity);

	/* adds effects to paddles */
	static WidthBonus* make_width_bonus(const Point &initial_position, const Vector& initial_velocity);
};