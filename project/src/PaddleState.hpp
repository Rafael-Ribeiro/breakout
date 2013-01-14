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

	virtual bool collision_filter(Body &other);
};

class NormalPaddleState : public PaddleState
{
public:
	bool collision_updates_physics(Body &other);
	bool collision_handle(Contact &contact);

	void draw(QPainter& painter) const;
};
