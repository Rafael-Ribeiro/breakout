#pragma once

#include <QPainter>

#include "Box.hpp"
#include "Movable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Drawable.hpp"
#include "PaddleState.hpp"

class PaddleFactory; // forward declaration (used "too soon")
class Player; // forward declaration (Paddle included on Player)
class BreakoutWorld;

class Paddle : public Box, public Movable, public Drawable
{
	static const unsigned int BASE_WIDTH;
	static const unsigned int BASE_HEIGHT;
	static const double VELOCITY;

	friend PaddleFactory;
	friend Player;
	friend BreakoutWorld;

	Player *_player;
	PaddleState *_state;

protected:
	Paddle(const Point &initial_position);

	Player* & player();

	void set_state(PaddleState *state);
	PaddleState * const & state() const;

public:
	virtual ~Paddle();

	Player* const & player() const;

	void draw(QPainter& painter) const;
};

class PaddleFactory
{
public:
	static Paddle* makeNormalPaddle(const Point &initial_position);
};