#pragma once

#include <QPainter>

#include "Box.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Drawable.hpp"
#include "BrickState.hpp"

class BrickFactory; // forward declaration (used "too soon")
class BreakoutWorld;

class Brick : public Box, public Drawable
{
	BrickState* _state;

	friend BrickFactory;
	friend BreakoutWorld;

protected:
	Brick(const Point &initial_position);
	void set_state(BrickState* state);

	BrickState * const & state() const;

public:
	static const unsigned int BASE_WIDTH;
	static const unsigned int BASE_HEIGHT;

	virtual ~Brick();

	void draw(QPainter& painter) const;
	bool hit_once();
	bool hit_all();
};

class BrickFactory
{
public:
	static Brick* makeNormalBrick(const Point &initial_position, QColor color, unsigned int hits);
	static Brick* makeGlassBrick(const Point &initial_position);
	static Brick* makeConcreteBrick(const Point &initial_position);
};