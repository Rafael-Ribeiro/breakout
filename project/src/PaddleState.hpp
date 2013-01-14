#pragma once

#include "State.hpp"

class Paddle;

class PaddleState : public State
{
	friend Paddle;

protected:
	Paddle* paddle;

	virtual ~PaddleState();
	void set_paddle(Paddle* paddle);
};

class NormalPaddleState : public PaddleState
{
public:
	void draw(QPainter& painter) const;
};
