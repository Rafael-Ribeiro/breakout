#pragma once

#include "State.hpp"

class Brick;

class BrickState : public State
{
	friend Brick;

protected:
	Brick* brick;

	virtual ~BrickState();
	void setBrick(Brick* brick);
};

class NormalBrickState : public BrickState
{
	unsigned int hits;

public:
	NormalBrickState(unsigned int hits);
	
	bool pre_collision(Body &other);
	bool post_collision(Contact &contact);
	void draw(QPainter& painter) const;
};

class GlassBrickState : public BrickState
{
public:
	bool pre_collision(Body &other);
	bool post_collision(Contact &contact);
	void draw(QPainter& painter) const;
};

class ConcreteBrickState : public BrickState
{
public:
	bool pre_collision(Body &other);
	bool post_collision(Contact &contact);
	void draw(QPainter& painter) const;
};
