#pragma once

#include "State.hpp"

class Ball;

class BallState : public State
{
	friend Ball;

protected:
	Ball* ball;

	virtual ~BallState();
	void set_ball(Ball* ball);

	virtual bool collision_filter(Body &other);
};

class NormalBallState : public BallState
{
public:
	bool collision_updates_physics(Body &other);
	bool collision_handle(Contact &contact);

	void draw(QPainter& painter) const;
};

class FireBallState : public BallState
{
public:
	bool collision_updates_physics(Body &other);
	bool collision_handle(Contact &contact);
	
	void draw(QPainter& painter) const;
};

class PhantomBallState : public BallState
{
public:
	bool collision_updates_physics(Body &other);
	bool collision_handle(Contact &contact);
	
	void draw(QPainter& painter) const;
};
