#pragma once

#include "Paddle.hpp"

// forward declaration (Bonus includes Player)
class Bonus;

class Player
{
	Paddle *_paddle;
	unsigned int score;

protected:
	Player(Paddle *paddle);
	virtual ~Player();

public:
	void left();
	void right();
	void stop();

	void redeem(Bonus &bonus, BreakoutWorld& world);
	virtual void step(const BreakoutWorld &world, const double &dt) = 0;

	void add_score(int value);
	void restart();
	
	Paddle * const & paddle() const;
};