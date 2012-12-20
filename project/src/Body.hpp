#pragma once

#include "Contact.hpp"
#include "Point.hpp"

class Body
{
	const static Vector VELOCITY;

protected:
	Body() {}

	void init(const double &density, const Point &osition);

	double _density;
	Point _position;

public:
	virtual ~Body() {};

	virtual const Vector& velocity() const;

	double& density();
	const double& density() const;

	Point& position();
	const Point& position() const;

	Contact do_collision(Body &other); 
	virtual void on_collision(Body &other, Contact &contact) = 0;
};

/* forward declarations */
class Box;
class Circle;

Contact do_collision(Box &b1, Box &b2);
Contact do_collision(Box &b, Circle &c);
Contact do_collision(Circle &c1, Circle &c2);
