#pragma once
#pragma once

#include "BreakoutWorld.hpp"
#include "CPUStrategy.hpp"
#include "Player.hpp"

class CPUStrategyMultiton; // forward declaration (CPUStrategyMultiton already includes CPUStrategy)

class NullCPUStrategy : public CPUStrategy
{
	static NullCPUStrategy instance;

protected:
	NullCPUStrategy();

public:
	const NullCPUStrategy& get_instance();
	void step(Player &player, const BreakoutWorld &world, const double &dt) const;
};
