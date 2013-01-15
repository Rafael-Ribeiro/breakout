#pragma once

#include <QPainter>

#include "Box.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Drawable.hpp"
#include "BrickState.hpp"

class BrickFactory; // forward declaration (used "too soon")

class Brick : public Box, public Drawable
{
	BrickState* state;

	friend BrickFactory;

protected:
	Brick(const Point &initial_position);
	void set_state(BrickState* state);

public:
	static const unsigned int BASE_WIDTH;
	static const unsigned int BASE_HEIGHT;

	virtual ~Brick();

	BrickState const * get_state() const;

	void draw(QPainter& painter) const;
	bool hit();
};

class BrickFactory
{
public:
	static Brick* makeNormalBrick(const Point &initial_position, QColor color, unsigned int hits);
	static Brick* makeGlassBrick(const Point &initial_position);
	static Brick* makeConcreteBrick(const Point &initial_position);
};