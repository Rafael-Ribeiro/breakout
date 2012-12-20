#pragma once

#include <QPainter>

class Drawable
{

public:
	Drawable() { };
	virtual ~Drawable() { };

	virtual void draw(QPainter &frame) const = 0;
};