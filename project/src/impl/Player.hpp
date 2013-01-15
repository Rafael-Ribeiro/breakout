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
	// this->_paddle->velocity() = Vector(-1, 0) * Paddle::VELOCITY;
	this->_paddle->velocity() += Vector(-20, 0);
}

void Player::right()
{
	// this->_paddle->velocity() = Vector(1, 0) * Paddle::VELOCITY;
	this->_paddle->velocity() += Vector(20, 0);
}

void Player::stop()
{
	this->_paddle->velocity() *= 0.5;
}

void Player::redeem(Bonus &bonus, BreakoutWorld& world)
{
	bonus.execute(world, *this);
}

Paddle * const & Player::paddle() const
{
	return this->_paddle;
}
