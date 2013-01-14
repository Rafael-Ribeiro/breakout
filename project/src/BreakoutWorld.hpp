#pragma once

#include "World.hpp"

#include "Ball.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"

class BreakoutWorld : public World
{
	typedef World super;

	set<Ball*> _balls;
	set<Brick*> _bricks;
	set<Paddle*> _paddles;

public:
	BreakoutWorld();

	void add(Body *body);
	void remove(Body *body);

	const set<Ball*>& balls() const;
	const set<Brick*>& bricks() const;
	const set<Paddle*>& paddles() const;	
};