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

class BonusFactory
{
public:
	static Bonus* make_random_bonus(const Point &initial_position, const Vector& initial_velocity);
	static SpeedBonus* make_speed_bonus(const Point &initial_position, const Vector& initial_velocity);
};