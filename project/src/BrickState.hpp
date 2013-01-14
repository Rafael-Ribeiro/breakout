#pragma once

#include "State.hpp"

class Brick;

class BrickState : public State
{
	friend Brick;

protected:
	Brick* brick;

	virtual ~BrickState();
	void set_brick(Brick* brick);

	virtual bool hit() = 0;
};

class NormalBrickState : public BrickState
{
	unsigned int hits;

public:
	NormalBrickState(unsigned int hits);

	void draw(QPainter& painter) const;
	bool hit();
};

class GlassBrickState : public BrickState
{
public:
	void draw(QPainter& painter) const;
	bool hit();
};

class ConcreteBrickState : public BrickState
{
public:
	void draw(QPainter& painter) const;
	bool hit();
};
