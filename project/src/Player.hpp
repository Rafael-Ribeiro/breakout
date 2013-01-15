#pragma once

#include "Paddle.hpp"

// forward declaration (Bonus includes Player)
class Bonus;

class Player
{
	Paddle *_paddle;
	unsigned int _score;

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
	
	const unsigned int& score() const;
	Paddle * const & paddle() const;
};