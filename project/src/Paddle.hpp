#pragma once

#include <QPainter>

#include "Box.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Drawable.hpp"
#include "PaddleState.hpp"

class Paddle : public Box, public Movable, public Drawable
{
	static const unsigned int BASE_WIDTH;
	static const unsigned int BASE_HEIGHT;

	PaddleState* state;

public:
	Paddle(const Point &initial_position);
	virtual ~Paddle();

	void set_state(PaddleState* state);

	bool collision_filter(Body &other);
	bool collision_updates_physics(Body &other);
	bool collision_handle(Contact &contact);

	void draw(QPainter& painter) const;
};

class PaddleFactory
{
public:
	static Paddle* makeNormalPaddle(const Point &initial_position);
};