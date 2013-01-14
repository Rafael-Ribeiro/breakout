#pragma once

#include <set>

#include "Body.hpp"
#include "Movable.hpp"
#include "AbstractCollisionMediator.hpp"

using namespace std;

class World : public AbstractCollisionMediator
{
	set<Body*> _bodies;
	set<Movable*> _movables;

protected:
	World();

public:
	virtual ~World();

    const set<Body*>& bodies() const;

	virtual void add(Body* body);
	virtual void remove(Body* body);

	void step(const double &dt);
};