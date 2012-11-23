#include <cmath>
#include <limits>

#include "../Body.hpp"

using namespace std;

Point& Body::position()
{
	return this->_position;
}

const Point& Body::position() const
{
	return this->_position;
}

Contact Body::do_collision(Body &other)
{
	Contact contact;

	Box *b1, *b2;
	Circle *c1, *c2;

	b1 = dynamic_cast<Box*>(this);
	b2 = dynamic_cast<Box*>(&other);

	c1 = dynamic_cast<Circle*>(this);
	c2 = dynamic_cast<Circle*>(&other);

	if (b1 && b2)
		contact = ::do_collision(*b1, *b2);

	else if (b1 && c2)
		contact = ::do_collision(*b1, *c2);

	else if (b2 && c1)
		contact = ::do_collision(*b2, *c1);

	else /* if (b2 && c2) */
		contact = ::do_collision(*b2, *c2);

	return contact;
}

Contact do_collision(Box &b1, Box &b2)
{
	/* TODO do_collision */
	return Contact();
}

Contact do_collision(Box &b, Circle &c)
{
	/* TODO do_collision */
	return Contact();
}

Contact do_collision(Circle &c1, Circle &c2)
{
	Contact contact;

	Vector dx = c1.position() - c2.position();
	double sqrd_distance = dx.sqrd_length();
	double sqrd_radius = c1.radius() * c1.radius() + c2.radius() * c2.radius();

	/* no point collision */
	if (sqrd_distance > sqrd_radius)
		return contact;

	if (dx.sqrd_length() > numeric_limits<double>::epsilon())
	{
		contact.normal() = dx;
		contact.normal().normalize();

	} else
		contact.normal() = Vector(1, 0);

	/* single point collision */
	if (fabs(sqrd_distance - sqrd_radius) < numeric_limits<double>::epsilon())
	{
		contact.points().push_back(c1.position() + contact.normal() * c1.radius());
		return contact;
	}

	/* two point collision */
	/* FIXME: missing dxx, dy */
	Vector dxx = contact.normal() * 1;
	Vector dy = contact.normal().normal() * 1;
	contact.points().push_back(c1.position() + dxx + dy);
	contact.points().push_back(c1.position() + dxx - dy);

	return contact;
}
