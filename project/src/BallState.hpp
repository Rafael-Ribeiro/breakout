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
};

class NormalBallState : public BallState
{
public:
	void draw(QPainter& painter) const;
};

class FireBallState : public BallState
{
public:
	void draw(QPainter& painter) const;
};

class PhantomBallState : public BallState
{
public:
	void draw(QPainter& painter) const;
};
