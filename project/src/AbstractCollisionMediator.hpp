#pragma once

#include "Body.hpp"
#include "Contact.hpp"

class AbstractCollisionMediator
{
protected:
	virtual bool collision_filter(Body &a, Body &b) = 0;
	virtual bool collision_updates_physics(Body &a, Body &other) = 0;
	virtual void collision_handle(Contact &contact) = 0;

	virtual void add(Body* body) = 0;
	virtual void remove(Body* body) = 0;
};