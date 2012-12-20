#pragma once

#include <set>

#include "Body.hpp"
#include "Movable.hpp"

using namespace std;

class Engine
{
	set<Body*> _bodies;
	set<Movable*> _movables;

public:
	Engine();
	~Engine();

    const set<Body*>& bodies() const;

	void step(const double &dt);
};