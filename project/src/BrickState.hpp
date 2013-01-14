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

	virtual bool collision_filter(Body &other);
};

class NormalBrickState : public BrickState
{
	unsigned int hits;

public:
	NormalBrickState(unsigned int hits);
	
	bool collision_updates_physics(Body &other);
	bool collision_handle(Contact &contact);

	void draw(QPainter& painter) const;
};

class GlassBrickState : public BrickState
{
public:
	bool collision_updates_physics(Body &other);
	bool collision_handle(Contact &contact);

	void draw(QPainter& painter) const;
};

class ConcreteBrickState : public BrickState
{
public:
	bool collision_updates_physics(Body &other);
	bool collision_handle(Contact &contact);

	void draw(QPainter& painter) const;
};
