#include "../Player.hpp"

Player::Player()
	: _paddle(NULL), _score(0)
{
}

Player::~Player()
{
}

void Player::paddle(Paddle *paddle)
{
	this->_paddle = paddle;
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

void Player::add_score(int value)
{
	this->_score += value;
}

void Player::redeem(Bonus &bonus, BreakoutWorld& world)
{
	bonus.execute(world, *this);
}

void Player::restart()
{
	this->_score = 0;
	this->_paddle->hwidth() = Paddle::BASE_WIDTH/2;
}

const unsigned int& Player::score() const
{
	return this->_score;
}

Paddle * const & Player::paddle() const
{
	return this->_paddle;
}
