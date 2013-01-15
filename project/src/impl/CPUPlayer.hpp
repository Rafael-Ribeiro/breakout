#include "../CPUPlayer.hpp"

CPUPlayer::CPUPlayer(Paddle *paddle, const CPUStrategy *strategy)
	: super(paddle), strategy(strategy)
{
}

void CPUPlayer::step(const BreakoutWorld &world, const double &dt)
{
	this->strategy->step(*this, world, dt);
}