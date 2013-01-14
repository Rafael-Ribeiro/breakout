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
	BrickState* state;

public:
	static const unsigned int BASE_WIDTH;
	static const unsigned int BASE_HEIGHT;

	Brick(const Point &initial_position);
	virtual ~Brick();

	void set_state(BrickState* state);
	BrickState const *  get_state() const;

	void draw(QPainter& painter) const;
	bool hit();
};

class BrickFactory
{
public:
	static Brick* makeNormalBrick(const Point &initial_position, unsigned int hits);
	static Brick* makeGlassBrick(const Point &initial_position);
	static Brick* makeConcreteBrick(const Point &initial_position);
};