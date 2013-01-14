#include <cmath>
#include <limits>
#include <cassert>

#include "../common.hpp"

#include "../Body.hpp"
#include "../Box.hpp"
#include "../Circle.hpp"

using namespace std;

const Vector Body::VELOCITY = Vector(0, 0);

void Body::init(const Point &position)
{
	this->_position = position;
}

const Vector& Body::velocity() const
{
	return Body::VELOCITY;
}

Point& Body::position()
{
	return this->_position;
}

const Point& Body::position() const
{
	return this->_position;
}

void Body::step(const double &dt)
{
	MARKUSED(dt);
}

bool Body::collides(Box &b1, Box &b2)
{
	Vector dp = b2.position() - b1.position();
	double ddx = fabs(dp.x()) - b1.hwidth() - b2.hwidth();
	double ddy = fabs(dp.y()) - b1.hheight() - b2.hheight();

	return ddx <= numeric_limits<double>::epsilon() && ddy <= numeric_limits<double>::epsilon();
}

bool Body::collides(Box &b, Circle &c)
{
	double cx = fabs(c.position().x() - b.position().x());
	double xd = b.hwidth() + c.radius();

	if (cx > xd)
		return false;

	double cy = fabs(c.position().y() - b.position().y());
	double yd = b.hheight() + c.radius();

	if (cy > yd)
		return false;

	if (cx <= b.hwidth() || cy <= b.hheight())
		return true;

	double xcd = cx - b.hwidth();
	double ycd = cy - b.hheight();
	double xcds = xcd * xcd;
	double ycds = ycd * ycd;
	double maxcds = c.radius() * c.radius();

	return xcds + ycds - maxcds <= numeric_limits<float>::epsilon();
}

bool Body::collides(Circle &c1, Circle &c2)
{
	Vector dp = c1.position() - c2.position();
	double sqrd_distance = dp.sqrd_length();
	double sqrd_radius = c1.radius() + c2.radius();
	sqrd_radius *= sqrd_radius;

	return sqrd_distance <= sqrd_radius;
}

Contact Body::do_collision(Body &other, const double& dt)
{
	Contact contact;

	Box *b1, *b2;
	Circle *c1, *c2;

	b1 = dynamic_cast<Box*>(this);
	b2 = dynamic_cast<Box*>(&other);

	c1 = dynamic_cast<Circle*>(this);
	c2 = dynamic_cast<Circle*>(&other);

	if (b1 && b2)
		contact = Body::do_collision(*b1, *b2, dt);

	else if (b1 && c2)
		contact = Body::do_collision(*b1, *c2, dt);

	else if (b2 && c1)
		contact = Body::do_collision(*b2, *c1, dt);

	else /* if (c1 && c2) */
		contact = Body::do_collision(*c1, *c2, dt);

	return contact;
}

Contact Body::do_collision(Box &b1, Box &b2, const double& dt)
{
	MARKUSED(dt);

	if (!Body::collides(b1, b2))
		return Contact();

	// Vector dv = b2.velocity() - b1.velocity();
	Vector dv = b1.velocity() - b2.velocity();

	double tf = -numeric_limits<double>::max();	
	double tl = numeric_limits<double>::max();

	if (dv.x() < -numeric_limits<double>::epsilon())
	{
//		assert(b2.right() >= b1.left());

		if (b1.right() - b2.left() < numeric_limits<double>::epsilon()) // b1.right() <= b2.left()
			tf = max((b1.right() - b2.left()) / dv.x(), tf);

		if (b2.right() - b1.left() > -numeric_limits<double>::epsilon()) // b2.right() >= b1.left()
			tl = min((b1.left() - b2.right()) / dv.x(), tl);

	} else if (dv.x() > numeric_limits<double>::epsilon())
	{
//		assert(b2.left() <= b1.right());

		if (b2.right() - b1.left() < numeric_limits<double>::epsilon()) // b2.right() <= b1.left()
			tf = max((b1.left() - b2.right()) / dv.x(), tf);

		if (b1.right() - b2.left() > -numeric_limits<double>::epsilon()) // b1.right() >= b2.left()
			tl = min((b1.right() - b2.left()) / dv.x(), tl);
	}

	// TODO:
	if (tf > tl)
		return Contact();

	if (dv.y() < numeric_limits<double>::epsilon()) // dv.y() < 0
	{
//		assert(b2.top() <= b1.bottom());

		if (b1.top() - b2.bottom() < numeric_limits<double>::epsilon()) // b1.top() <= b2.bottom() 
			tf = max((b1.top() - b2.bottom()) / dv.y(), tf);

		if (b2.top() - b1.bottom() > -numeric_limits<double>::epsilon()) // b2.top() >= b1.bottom()
			tl = min((b1.bottom() - b2.top()) / dv.y(), tl);

	} else if (dv.y() > -numeric_limits<double>::epsilon())
	{
//		assert(b2.bottom() <= b1.top());

		if (b2.top() - b1.bottom() < numeric_limits<double>::epsilon()) // b2.top() <= b1.bottom()
			tf = max((b1.bottom() - b2.top()) / dv.y(), tf);

		if (b1.top() - b2.bottom() > -numeric_limits<double>::epsilon()) // b1.top() >= b2.bottom()
			tl = min((b1.top() - b2.bottom()) / dv.y(), tl);		
	}

	if (tf <= tl)
		return Contact();

	/* FIXME: normal vector not used yet so dont compute it */
	Vector normal(1, 0);

	return Contact(-tl, normal, &b1, &b2);
}

Contact Body::do_collision(Box &b, Circle &c, const double& dt)
{
	if (!Body::collides(b, c))
		return Contact();

	// binary search

	double delta_t = dt;
	double low = -dt;
	double high = 0;
	double middle;

	Point bp = b.position();
	Point cp = c.position();

	while (delta_t > numeric_limits<double>::epsilon())
	{
		delta_t /= 2;
		middle = low + delta_t;

		b.step(middle);
		c.step(middle);

		if (collides(b, c))
			high = middle;
		else
			low = middle;

		b.position() = bp;
		c.position() = cp;
	}

	b.step(high);
	c.step(high);

	Vector normal;
	Vector dp = c.position() - b.position();
	
	if (c.position().x() > b.right())
	{

		if (c.position().y() > b.top())
			normal = (dp - Vector(b.hwidth(), b.hheight())).normalize();

		else if (c.position().y() < b.bottom())
			normal = (dp - Vector(b.hwidth(), -b.hheight())).normalize();

		else
			normal = Vector(1, 0);

	} else if (c.position().x() < b.left())
	{
		if (c.position().y() > b.top())
			normal = (dp - Vector(-b.hwidth(), b.hheight())).normalize();

		else if (c.position().y() < b.bottom())
			normal = (dp - Vector(-b.hwidth(), -b.hheight())).normalize();

		else
			normal = Vector(-1, 0);

	} else
	{
		if (c.position().y() < b.position().y())
			normal = Vector(0, -1);

		else
			normal = Vector(0, 1);
	}

	b.position() = bp;
	c.position() = cp;

	return Contact(high, normal, &b, &c);
}

Contact Body::do_collision(Circle &c1, Circle &c2, const double& dt)
{
	MARKUSED(dt);

	if (!Body::collides(c1, c2))
		return Contact();

	Vector dp = c1.position() - c2.position();
	Vector dv = c1.velocity() - c2.velocity();
	double sqrd_radius = c1.radius() + c2.radius();
	sqrd_radius *= sqrd_radius;

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
		t2 = (-b + sqrtdisc) / (2 * a);

		t = std::min(t1, t2);
	}

	if (dp != Vector(0, 0))
		return Contact(t, dp.normalize(), &c1, &c2);

	return Contact(t, -dv.normalize(), &c1, &c2);
}