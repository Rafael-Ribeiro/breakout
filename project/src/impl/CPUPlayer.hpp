#include "../CPUPlayer.hpp"

CPUPlayer::CPUPlayer(const CPUStrategy *strategy)
	: strategy(strategy)
{
}

void CPUPlayer::step(const BreakoutWorld &world, const double &dt)
{
	this->strategy->step(*this, world, dt);
}