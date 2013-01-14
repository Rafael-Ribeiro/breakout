#pragma once

#include <QPainter>

#include "Box.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Drawable.hpp"
#include "BrickState.hpp"

class Brick : public Box, public Drawable
{
	static const unsigned int BASE_WIDTH;
	static const unsigned int BASE_HEIGHT;

	BrickState* state;

public:
	Brick(const Point &initial_position);
	virtual ~Brick();

	bool pre_collision(Body &other);
	bool post_collision(Contact &contact);
	void draw(QPainter& painter) const;

	void setState(BrickState* state);
};

class BrickFactory
{
public:
	static Brick* makeNormalBrick(const Point &initial_position, unsigned int hits);
	static Brick* makeGlassBrick(const Point &initial_position);
	static Brick* makeConcreteBrick(const Point &initial_position);
};