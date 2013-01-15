#pragma once

#include "World.hpp"

#include "Ball.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"
#include "Player.hpp"

class BreakoutWorld : public World
{
	typedef World super;

	set<Ball*> _balls;
	set<Brick*> _bricks;
	set<Paddle*> _paddles;
	Player* _players[2];

public:
	static const unsigned int WIDTH;
	static const unsigned int HEIGHT;

	BreakoutWorld();

	void add(Body *body);
	void remove(Body *body);

	bool collision_filter(Body &a, Body &b);
	bool collision_updates_physics(Body &a, Body &other);
	void collision_handle(Contact &contact);

	const set<Ball*>& balls() const;
	const set<Brick*>& bricks() const;
	const set<Paddle*>& paddles() const;

	bool load_level(string level_filename_path);

	virtual void step(const double& dt);
};