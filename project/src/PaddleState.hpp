#pragma once

#include "State.hpp"

class Paddle;

class PaddleState : public State
{
	friend Paddle;

protected:
	Paddle* paddle;

	virtual ~PaddleState();
	void setPaddle(Paddle* paddle);
};

class NormalPaddleState : public PaddleState
{
public:
	bool pre_collision(Body &other);
	bool post_collision(Contact &contact);
	void draw(QPainter& painter) const;
};
