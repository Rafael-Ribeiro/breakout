#pragma once

#include "BreakoutWorld.hpp"
#include "CPUStrategy.hpp"
#include "Player.hpp"

class CPUStrategyMultiton; // forward declaration (CPUStrategyMultiton already includes CPUStrategy)

class FirstBallCPUStrategy : public CPUStrategy
{
	friend CPUStrategyMultiton;

protected:
	FirstBallCPUStrategy();

public:
	void step(Player &player, const BreakoutWorld &world, const double &dt) const;
};
