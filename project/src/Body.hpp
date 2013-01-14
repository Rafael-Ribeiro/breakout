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

	virtual bool collision_filter(Body &other) = 0;
	virtual bool collision_updates_physics(Body &other) = 0;
	virtual bool collision_handle(Contact &contact) = 0;

	Contact get_collision_contact(Body &other, const double &dt); 

	static Contact get_collision_contact(Box &b1, Box &b2, const double &dt);
	static Contact get_collision_contact(Box &b, Circle &c, const double &dt);
	static Contact get_collision_contact(Circle &c1, Circle &c2, const double &dt);

	static bool collides(Box &b1, Box &b2);
	static bool collides(Box &b, Circle &c);
	static bool collides(Circle &c1, Circle &c2);

};

//
