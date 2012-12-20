#include <cmath>
#include <limits>
#include <cassert>

#include "../Body.hpp"
#include "../Box.hpp"
#include "../Circle.hpp"

using namespace std;

const Vector Body::VELOCITY = Vector(0, 0);

void Body::init(const double &density, const Point &position)
{
	this->_density = density;
	this->_position = position;
}

const Vector& Body::velocity() const
{
	return Body::VELOCITY;
}

double& Body::density()
{
	return this->_density;
}

const double& Body::density() const
{
	return this->_density;
}

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
	double b1half_height, b1half_width, b2half_height, b2half_width;

	b1half_height = b1.height() / 2;
	b1half_width = b1.width() / 2;

	b2half_height = b2.height() / 2;
	b2half_width = b2.width() / 2;

	double b1top, b1bottom, b1left, b1right;
	double b2top, b2bottom, b2left, b2right;

	b1top = b1.position().y() + b1half_height;
	b1bottom = b1.position().y() - b1half_height;
	b1left = b1.position().x() - b1half_width;
	b1right = b1.position().x() + b1half_width;

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

	Vector dp = c1.position() - c2.position();
	Vector dv = c1.velocity() - c2.velocity();

	double sqrd_distance = dp.sqrd_length();
	double sqrd_radius = c1.radius() + c2.radius();
	sqrd_radius *= sqrd_radius;

	/* no point collision */
	if (sqrd_distance > sqrd_radius)
		return contact;

	double a, b, c;
	a = dv * dv;
	b = dp * dv * 2;
	c = dp * dp - sqrd_radius;

	double discriminant = b * b - 4 * a * c;
	double t;

	assert (discriminant > -numeric_limits<double>::epsilon());

	if (discriminant < numeric_limits<double>::epsilon())
		t = - b / (2 * a);
	else
	{
		double t1, t2, sqrtdisc;
		sqrtdisc = sqrt(discriminant);

		t1 = (-b - sqrtdisc) / (2 * a);
		t2 = (-b - sqrtdisc) / (2 * a);

		t = std::min(t1, t2);
	}

	contact.normal() = dp;
	contact.normal().normalize();
	contact.points().push_back(c1.position() + contact.normal() * c1.radius());
	return contact;
}