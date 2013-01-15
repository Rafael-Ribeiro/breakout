#include "../HumanPlayer.hpp"

HumanPlayer::HumanPlayer(Paddle *paddle, Qt::Key left_key, Qt::Key right_key)
	: super(paddle), left_key(left_key), right_key(right_key)
{
}

void HumanPlayer::step(const double &dt)
{
	// TODO
}