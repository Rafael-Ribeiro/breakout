#pragma once

#include "Body.hpp"
#include "Box.hpp"
#include "Circle.hpp"

/* forward declaration */
class BreakoutFrame;

template <class B>
class Drawable
{
	B *body;

public:
	Drawable(B *body)
		: body(body)
	{
	}

	void draw(BreakoutFrame &frame) const;
};