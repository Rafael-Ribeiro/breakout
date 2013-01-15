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

class Paddle : public Box, public Movable, public Drawable
{
	static const unsigned int BASE_WIDTH;
	static const unsigned int BASE_HEIGHT;
	static const double VELOCITY;

	friend PaddleFactory;
	friend Player;

	Player *player;
	PaddleState *state;

protected:
	Paddle(const Point &initial_position);

	void set_player(Player *player);
	void set_state(PaddleState *state);

public:
	virtual ~Paddle();

	PaddleState const * get_state() const;
		
	void draw(QPainter& painter) const;
};

class PaddleFactory
{
public:
	static Paddle* makeNormalPaddle(const Point &initial_position);
};