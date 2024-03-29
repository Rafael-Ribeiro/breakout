#pragma once

#include "BreakoutWorld.hpp"
#include "CPUStrategy.hpp"
#include "Player.hpp"

class CPUStrategyMultiton; // forward declaration (CPUStrategyMultiton already includes CPUStrategy)

class FirstBallCPUStrategy : public CPUStrategy
{
	static FirstBallCPUStrategy instance;

protected:
	FirstBallCPUStrategy();

public:
	const FirstBallCPUStrategy& get_instance();
	void step(Player &player, const BreakoutWorld &world, const double &dt) const;
};
