#pragma once

#include "BreakoutWorld.hpp"
#include "Player.hpp"

class CPUStrategy
{
public:
	virtual void step(Player &player, const BreakoutWorld &world, const double &dt) const = 0;
};