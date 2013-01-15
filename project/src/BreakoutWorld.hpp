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
	set<Bonus*> _bonuses;
	set<Drawable*> _drawables;
	
	Player* _players[2];

public:
	static const unsigned int WIDTH;
	static const unsigned int HEIGHT;

	static const unsigned int GOAL_SCORE;
	static const unsigned int BONUS_SCORE;
	static const unsigned int BRICK_SCORE;

	BreakoutWorld();

	void add(Body *body);
	void remove(Body *body);

	void clear();
	void restart();
	bool load_level(string level_filename_path);

	bool collision_filter(Body &a, Body &b);
	bool collision_updates_physics(Body &a, Body &other);
	void collision_handle(Contact &contact);

	const set<Ball*>& balls() const;
	const set<Brick*>& bricks() const;
	const set<Paddle*>& paddles() const;
	const set<Bonus*>& bonuses() const;
	const set<Drawable*>& drawables() const;
	Player* const * players() const; 

	virtual void step(const double& dt);
};