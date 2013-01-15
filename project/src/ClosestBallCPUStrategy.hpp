#pragma once

#include "BreakoutWorld.hpp"
#include "CPUStrategy.hpp"
#include "Player.hpp"

class CPUStrategyMultiton; // forward declaration (CPUStrategyMultiton already includes CPUStrategy)

class ClosestBallCPUStrategy : public CPUStrategy
{
	friend CPUStrategyMultiton;

protected:
	ClosestBallCPUStrategy();

public:
	void step(Player &player, const BreakoutWorld &world, const double &dt) const;
};
