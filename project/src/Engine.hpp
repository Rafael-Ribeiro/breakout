#pragma once

#include <set>

#include "Body.hpp"
#include "Movable.hpp"

using namespace std;

class Engine
{
	set<Body*> bodies;
	set<Movable*> movables;

public:
	void step(const double &dt);
};