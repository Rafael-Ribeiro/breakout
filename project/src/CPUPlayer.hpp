#pragma once

#include <QKeyEvent>

#include "CPUStrategy.hpp"
#include "Paddle.hpp"

class CPUPlayer : public Player
{
	typedef Player super;

	const CPUStrategy *strategy;

public:
	CPUPlayer(const CPUStrategy *strategy);

	void step(const BreakoutWorld &world, const double &dt);
};