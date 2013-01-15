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
}

void Player::right()
{
	this->_paddle->velocity() = Vector(1, 0) * Paddle::VELOCITY;
}

void Player::stop()
{
	this->_paddle->velocity() = Vector(0, 0);
}

void Player::redeem(Bonus &bonus)
{
}

Paddle * const & Player::paddle() const
{
	return this->_paddle;
}
