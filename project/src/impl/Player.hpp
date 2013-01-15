#include "../Player.hpp"

Player::Player(Paddle *paddle)
	: paddle(paddle), score(0)
{
	this->paddle->set_player(this);
}

Player::~Player()
{
}

void Player::left()
{
	this->paddle->velocity() = Vector(-1, 0) * Paddle::VELOCITY;
}

void Player::right()
{
	this->paddle->velocity() = Vector(1, 0) * Paddle::VELOCITY;
}

void Player::stop()
{
	this->paddle->velocity() = Vector(0, 0);
}

void Player::redeem(Bonus &bonus)
{
}