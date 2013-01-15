#pragma once

#include <map>
#include <string>

class CPUStrategy;
class NullCPUStrategy;

class CPUStrategyMultiton
{
public:
	typedef std::map<const std::string, const CPUStrategy*> map_t;

	static void add(const std::string& name, const CPUStrategy* strategy);
	static const CPUStrategy* get(const std::string& name);

	static const map_t& strategies();

protected:
	CPUStrategyMultiton();

	static map_t _strategies;
	static const CPUStrategy* _default_strategy;

	friend NullCPUStrategy;
};