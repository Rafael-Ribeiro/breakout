#pragma once

#include "ClosestBallCPUStrategy.hpp"
#include "FirstBallCPUStrategy.hpp"

class CPUStrategyMultiton
{
	static const ClosestBallCPUStrategy closest_ball_cpu_strategy;
	static const FirstBallCPUStrategy first_ball_cpu_strategy;

public:
	static const ClosestBallCPUStrategy& get_closest_ball_cpu_strategy_instance();
	static const FirstBallCPUStrategy& get_first_ball_cpu_strategy_instance();
};