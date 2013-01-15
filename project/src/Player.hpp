#pragma once

#include "Paddle.hpp"

// forward declaration (Bonus includes Player)
class Bonus;

class Player
{
	Paddle *paddle;
	unsigned int score;

protected:
	Player(Paddle *paddle);
	virtual ~Player();

	void left();
	void right();
	void stop();

public:
	void redeem(Bonus &bonus);
	virtual void step(double &dt) = 0;
};