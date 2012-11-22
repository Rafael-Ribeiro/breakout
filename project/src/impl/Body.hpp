#include "../Body.hpp"

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
	/* TODO do_collision */
	return Contact();
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
	/* TODO do_collision */
	return Contact();
}
