#include <cassert>

#include "Ball.hpp"
#include "Point.hpp"
#include "Vector.hpp"

void test1()
{
	Ball b(Point(0, 0), Vector(1, 0));
	b.step(1.0);

	assert(b.position() == Point(1, 0));
}

void test2()
{
	Ball b(Point(0, 0), Vector(1, 0));
	
	for (int i = 0; i < 10; i++)
	{
		b.step(1.0);
		b.velocity() = -b.velocity();
	}

	assert(b.position() == Point(0, 0));	
}

int main()
{
	test1();
	test2();
	return 0;
}