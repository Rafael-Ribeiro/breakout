#pragma once

#include "State.hpp"

class Ball;

class BallState : public State
{
	friend Ball;

protected:
	Ball* ball;

	virtual ~BallState();
	void setBall(Ball* ball);
};

class NormalBallState : public BallState
{
public:
	bool pre_collision(Body &other);
	bool post_collision(Contact &contact);
	void draw(QPainter& painter) const;
};

class FireBallState : public BallState
{
public:
	bool pre_collision(Body &other);
	bool post_collision(Contact &contact);
	void draw(QPainter& painter) const;
};

class PhantomBallState : public BallState
{
public:
	bool pre_collision(Body &other);
	bool post_collision(Contact &contact);
	void draw(QPainter& painter) const;
};
