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

	Ball* ball = dynamic_cast<Ball*>(ball);
	if (ball)
		this->_balls.insert(ball);

	Brick* brick = dynamic_cast<Brick*>(brick);
	if (brick)
		this->_bricks.insert(brick);

	Paddle* paddle = dynamic_cast<Paddle*>(paddle);
	if (paddle)
		this->_paddles.insert(paddle);
}

void BreakoutWorld::remove(Body *body)
{
	super::remove(body);

	Ball* ball = dynamic_cast<Ball*>(ball);
	if (ball)
		this->_balls.erase(ball);

	Brick* brick = dynamic_cast<Brick*>(brick);
	if (brick)
		this->_bricks.erase(brick);

	Paddle* paddle = dynamic_cast<Paddle*>(paddle);
	if (paddle)
		this->_paddles.erase(paddle);
}

const set<Ball*>& BreakoutWorld::balls() const
{
	return this->_balls;
}

const set<Brick*>& BreakoutWorld::bricks() const
{
	return this->_bricks;
}

const set<Paddle*>& BreakoutWorld::paddles() const
{
	return this->_paddles;
}