#include "../BreakoutWorld.hpp"

BreakoutWorld::BreakoutWorld() : World()
{
	for (unsigned int i = 0; i < 25; i++)
	{
		for (unsigned int j = 0; j < 10; j++)
		{
			Brick* brick = BrickFactory::makeNormalBrick(Point(48 * i + 25, 16 * j + 100), 1);
			this->add(brick);
		}
	}

	for (unsigned int i = 0; i < 25; i++)
	{
		for (unsigned int j = 0; j < 10; j++)
		{
			Brick* brick = BrickFactory::makeNormalBrick(Point(48 * i + 25, 16 * j + 500), 1);
			this->add(brick);
		}
	}

	Ball* missile = BallFactory::makeNormalBall(Point(500, 400), Vector(3.0, -200));
	this->add(missile);
}

void BreakoutWorld::add(Body *body)
{
	super::add(body);

	/* TODO */
}

void BreakoutWorld::remove(Body *body)
{
	super::remove(body);

	/* TODO */
}