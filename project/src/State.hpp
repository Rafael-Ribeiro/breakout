#pragma once

#include <QPainter>

#include "Body.hpp"
#include "Contact.hpp"

class State
{
public:
	virtual ~State() = 0;

	virtual void draw(QPainter& painter) const = 0;
};
