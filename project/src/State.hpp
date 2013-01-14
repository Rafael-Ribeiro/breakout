#pragma once

#include <QPainter>

#include "Body.hpp"
#include "Contact.hpp"

class State
{
public:
	virtual ~State() = 0;

	virtual bool collision_filter(Body &other) = 0;
	virtual bool collision_updates_physics(Body &other) = 0;
	virtual bool collision_handle(Contact &contact) = 0;

	virtual void draw(QPainter& painter) const = 0;
};
