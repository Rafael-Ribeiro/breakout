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

	virtual bool hit_once() = 0;
	virtual bool hit_all() = 0;
};

class NormalBrickState : public BrickState
{
	QColor _color;
	unsigned int _hits;
	unsigned int _remaining;

public:
	NormalBrickState(QColor color, unsigned int hits);

	void draw(QPainter& painter) const;
	bool hit_once();
	bool hit_all();
};

class GlassBrickState : public BrickState
{
public:
	void draw(QPainter& painter) const;
	bool hit_once();
	bool hit_all();
};

class ConcreteBrickState : public BrickState
{
public:
	void draw(QPainter& painter) const;
	bool hit_once();
	bool hit_all();
};
