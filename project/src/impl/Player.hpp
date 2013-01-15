#include "../Player.hpp"

Player::Player(Paddle *paddle)
	: _paddle(paddle), score(0)
{
	this->_paddle->player() = this;
}

Player::~Player()
{
}

void Player::left()
{
	this->_paddle->velocity() = Vector(-1, 0) * Paddle::VELOCITY;

/*	
	Vector acc(-20, 0);

	if (acc * this->_paddle->velocity() < 0)
		this->stop();

	this->_paddle->velocity() += acc;
*/
}

void Player::right()
{
	this->_paddle->velocity() = Vector(1, 0) * Paddle::VELOCITY;

/*	
	Vector acc(20, 0);

	if (acc * this->_paddle->velocity() < 0)
		this->stop();

	this->_paddle->velocity() += acc;
*/
}

void Player::stop()
{
	this->_paddle->velocity() = Vector(0, 0);

//	this->_paddle->velocity() *= 0.7;
}

void Player::redeem(Bonus &bonus, BreakoutWorld& world)
{
	bonus.execute(world, *this);
}

Paddle * const & Player::paddle() const
{
	return this->_paddle;
}
