#include <cassert>

#include "Ball.hpp"
#include "Box.hpp"
#include "Paddle.hpp"
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

void test_circle_circle_collision()
{
	Ball a(Point(0, 0), Vector(0, 0));
	Ball b(Point(30.0, 0), Vector(-10.0, 0));

	/* no collision */ 
	Contact c = a.do_collision(b, 0);		
	assert(!c);

	/* single point collision */ 
	b.position() = Point(20.0, 0);

	c = a.do_collision(b, 0);
	assert(c);
	assert(c.toc() == 0);

	/* double point collision */ 
	b.position() = Point(10.0, 0);

	c = a.do_collision(b, 0);
	assert(c);
	assert(c.toc() == -1);

	/* infinite point collision */ 
	b.position() = Point(0, 0);

	c = a.do_collision(b, 0);
	assert(c);
	assert(c.toc() == -2);

	/* double velocity */
	a.velocity() = Vector(10, 0);

	c = a.do_collision(b, 0);
	assert(c);
	assert(c.toc() == -1);

	/* uncollide */
	a.step(c.toc());
	b.step(c.toc());

	/* Single point collision again */
	c = a.do_collision(b, 0);
	assert(c);
	assert(c.toc() == 0);
}

void test_circle_box_collides()
{
	Paddle p(Point(0, 0), Vector(0, 0));
	Ball b(Point(0, 0), Vector(1, 0));

	assert(collides(p, b));

	b.position() = Point(0, 15);
	assert(collides(p, b));

	b.position() = Point(35, 0);
	assert(collides(p, b));

	b.position() = Point(0, 16);
	assert(!collides(p, b));

	b.position() = Point(25, 5) + Vector(1, 1) * 10 * sqrt(2)/2;
	assert(collides(p, b));

	b.position() += Point(0.1, 0.1);
	assert(!collides(p, b));

}

void test_box_box_collides()
{
	Paddle p1(Point(0, 0), Vector(0, 0));
	Paddle p2(Point(0, 20), Vector(0, 0));

	assert(!collides(p1, p2));

	/* collision is a line */
	p2.position() = Point(0, 10);
	assert(collides(p1, p2));

	/* collision is an area */
	p2.position() = Point(0, 5);
	assert(collides(p1, p2));

	/* collision is a point */
	p2.position() = Point(50, 10);
	assert(collides(p1, p2));
}

void test_box_box_collision()
{
	Paddle p1(Point(0, 0), Vector(0, 0));
	Paddle p2(Point(0, 20), Vector(0, -1));
	Contact c;

	assert(!do_collision(p1, p2, 0));

	/* collision is a line */
	p2.position() = Point(0, 10);
	c = do_collision(p1, p2, 0);
	assert(c);
	assert(c.toc() == 0);

	/* collision is an area */
	p2.position() = Point(0, 5);
	c = do_collision(p1, p2, 0);
	assert(c);

	cout << c.toc() << endl;
	assert(c.toc() == -5);

	/* collision is a point */
	p2.position() = Point(50, 10);
	assert(collides(p1, p2));
}

int main()
{
	test1();
	test2();

	test_circle_circle_collision();
	test_circle_box_collides();
	test_box_box_collides();
	test_box_box_collision();

	return 0;
}