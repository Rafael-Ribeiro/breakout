#pragma once

#include "Contact.hpp"
#include "Point.hpp"

/* forward declarations */
class Box;
class Circle;

class Body
{
	const static Vector VELOCITY;

protected:
	Body() {}

	void init(const Point &position);

	Point _position;

public:
	virtual ~Body() {};

	virtual const Vector& velocity() const;
	virtual void step(const double &dt);

	Point& position();
	const Point& position() const;

	virtual bool pre_collision(Body &other) = 0;
	virtual bool post_collision(Contact &contact) = 0;

	static bool collides(Box &b1, Box &b2);
	static bool collides(Box &b, Circle &c);
	static bool collides(Circle &c1, Circle &c2);

	Contact do_collision(Body &other, const double &dt); 
	static Contact do_collision(Box &b1, Box &b2, const double &dt);
	static Contact do_collision(Box &b, Circle &c, const double &dt);
	static Contact do_collision(Circle &c1, Circle &c2, const double &dt);
};


