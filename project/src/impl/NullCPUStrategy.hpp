#include "../NullCPUStrategy.hpp"

NullCPUStrategy NullCPUStrategy::instance;

NullCPUStrategy::NullCPUStrategy()
{
	CPUStrategyMultiton::_default_strategy = this;
}

const NullCPUStrategy& NullCPUStrategy::get_instance()
{
	return NullCPUStrategy::instance;
}

void NullCPUStrategy::step(Player &player, const BreakoutWorld &world, const double &dt) const
{
}