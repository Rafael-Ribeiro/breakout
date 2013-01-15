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
}

void Player::right()
{
}

void Player::stop()
{
}

void Player::redeem(Bonus &bonus)
{
}

void Player::step(double &dt) = 0
{
}
