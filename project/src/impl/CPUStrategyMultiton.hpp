#include "../CPUStrategyMultiton.hpp"

CPUStrategyMultiton::map_t CPUStrategyMultiton::_strategies;
const CPUStrategy* CPUStrategyMultiton::_default_strategy = NULL;

CPUStrategyMultiton::CPUStrategyMultiton()
{
}

void CPUStrategyMultiton::add(const std::string& name, const CPUStrategy* strategy)
{
	CPUStrategyMultiton::_strategies[name] = strategy;
}

const CPUStrategy* CPUStrategyMultiton::get(const std::string& name)
{
	CPUStrategyMultiton::map_t::const_iterator it = CPUStrategyMultiton::_strategies.find(name);

	if (it == CPUStrategyMultiton::_strategies.end())
		return CPUStrategyMultiton::_default_strategy;

	return it->second;
}

const CPUStrategyMultiton::map_t& CPUStrategyMultiton::strategies()
{
	return CPUStrategyMultiton::_strategies;
}