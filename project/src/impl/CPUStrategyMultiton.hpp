#include "../CPUStrategyMultiton.hpp"

const ClosestBallCPUStrategy CPUStrategyMultiton::closest_ball_cpu_strategy;
const FirstBallCPUStrategy CPUStrategyMultiton::first_ball_cpu_strategy;

const ClosestBallCPUStrategy& CPUStrategyMultiton::get_closest_ball_cpu_strategy_instance()
{
	return CPUStrategyMultiton::closest_ball_cpu_strategy;
}

const FirstBallCPUStrategy& CPUStrategyMultiton::get_first_ball_cpu_strategy_instance()
{
	return CPUStrategyMultiton::first_ball_cpu_strategy;
}