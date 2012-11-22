#pragma once

#include "Contact.hpp"
#include "Point.hpp"

class Body
{

protected:
	Body() {}

	Body(const Point &initial_position)
		: _position(initial_position)
	{
	}

	Point _position;

public:
	Contact do_collision(Body &other); 
	virtual void on_collision(Body &other, Contact &contact) = 0;

	Point& position();
	const Point& position() const;
};

/* forward declarations */
class Box;
class Circle;

Contact do_collision(Box &b1, Box &b2);
Contact do_collision(Box &b, Circle &c);
Contact do_collision(Circle &c1, Circle &c2);
