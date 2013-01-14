#pragma once

#include <QPainter>

#include "Body.hpp"
#include "Contact.hpp"

class State
{
public:
	virtual ~State() = 0;

	virtual bool pre_collision(Body &other) = 0;
	virtual bool post_collision(Contact &contact) = 0;
	virtual void draw(QPainter& painter) const = 0;
};
