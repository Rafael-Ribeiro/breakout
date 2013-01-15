#include <fstream>
#include <random>
#include <cmath>
#include <sys/time.h>

#include "jsoncpp/inc/json.h"

#include "../BreakoutWorld.hpp"

const double PI = std::atan(1.0) * 4;

const unsigned int BreakoutWorld::WIDTH = 1024;
const unsigned int BreakoutWorld::HEIGHT = 768;

BreakoutWorld::BreakoutWorld() : World()
{
	this->load_level("../levels/level1.json");

	Paddle *player_1_paddle = PaddleFactory::makeNormalPaddle(Point(512, 748));
	this->add(player_1_paddle);
}

void BreakoutWorld::add(Body *body)
{
	super::add(body);

	Ball* ball = dynamic_cast<Ball*>(body);
	if (ball)
		this->_balls.insert(ball);

	Brick* brick = dynamic_cast<Brick*>(body);
	if (brick)
		this->_bricks.insert(brick);

	Paddle* paddle = dynamic_cast<Paddle*>(body);
	if (paddle)
		this->_paddles.insert(paddle);
}

void BreakoutWorld::remove(Body *body)
{
	super::remove(body);

	Ball* ball = dynamic_cast<Ball*>(body);
	if (ball)
		this->_balls.erase(ball);

	Brick* brick = dynamic_cast<Brick*>(body);
	if (brick)
		this->_bricks.erase(brick);

	Paddle* paddle = dynamic_cast<Paddle*>(body);
	if (paddle)
		this->_paddles.erase(paddle);
}

bool BreakoutWorld::collision_filter(Body &a, Body &b)
{
	Ball* ball_a = dynamic_cast<Ball*>(&a);
	Ball* ball_b = dynamic_cast<Ball*>(&b);
	
/*
	Brick* brick_a = dynamic_cast<Brick*>(&a);
	Brick* brick_b = dynamic_cast<Brick*>(&b);
*/

	Paddle* paddle_a = dynamic_cast<Paddle*>(&a);
	Paddle* paddle_b = dynamic_cast<Paddle*>(&b);
	
	/* balls collide with everything */
	if (ball_a || ball_b)
	{
		/* except if any of them is a phantom*/
		if (ball_a && dynamic_cast<PhantomBallState * const>(ball_a->state()))
			return false;

		if (ball_b && dynamic_cast<PhantomBallState * const>(ball_b->state()))
			return false;

		return true;
	}

	/* paddles collide with everything but other paddles */
	if ((paddle_a && !paddle_b) || (paddle_b && !paddle_a)) // paddle_a ^ paddle_b
		return true;

	return false;
}

bool BreakoutWorld::collision_updates_physics(Body &a, Body &b)
{
	Ball* ball_a = dynamic_cast<Ball*>(&a);
	Ball* ball_b = dynamic_cast<Ball*>(&b);
	
	Brick* brick_a = dynamic_cast<Brick*>(&a);
	Brick* brick_b = dynamic_cast<Brick*>(&b);

	Paddle* paddle_a = dynamic_cast<Paddle*>(&a);
	Paddle* paddle_b = dynamic_cast<Paddle*>(&b);

	for (unsigned int i = 0; i < 2; i++)
	{
		if (ball_a)
		{
			/* ball vs everything */
			if (ball_b || paddle_b)
				return true;

			assert(brick_b);

			if (dynamic_cast<ConcreteBrickState * const>(brick_b->state()))
				return true;

			if (dynamic_cast<GlassBrickState * const>(brick_b->state()) || dynamic_cast<PhantomBallState * const>(ball_a))
				return false;

			return true;
		} else if (paddle_a)
		{
			/* paddle vs everything \ { ball } */
			cout << "TODO: paddle vs bonus and stuff" << endl;
		}

		swap(ball_a, ball_b);
		swap(brick_a, brick_b);
		swap(paddle_a, paddle_b);
	}

	assert(false);
	return false;
}

void BreakoutWorld::collision_handle(Contact &contact)
{
	bool delete_a = false, delete_b = false;

	Body *a = contact.body_a();
	Body *b = contact.body_b();
	
	Ball* ball_a = dynamic_cast<Ball*>(a);
	Ball* ball_b = dynamic_cast<Ball*>(b);
	
	Brick* brick_a = dynamic_cast<Brick*>(a);
	Brick* brick_b = dynamic_cast<Brick*>(b);

	Paddle* paddle_a = dynamic_cast<Paddle*>(a);
	Paddle* paddle_b = dynamic_cast<Paddle*>(b);

	Vector normal = contact.normal();

	for (unsigned int i = 0; i < 2; i++)
	{
		if (ball_a)
		{
			/* ball vs everything */
			if (ball_b)
			{
				ball_a->velocity() = normal.reflect(ball_a->velocity());
				ball_b->velocity() = -normal.reflect(ball_b->velocity());
				goto cleanup;
			}

			if (paddle_b)
			{
				ball_a->velocity() = normal.reflect(ball_a->velocity());
				goto cleanup;
			}

			assert(brick_b);

			delete_b = brick_b->hit();
			if (dynamic_cast<GlassBrickState * const>(brick_b->state()) || dynamic_cast<PhantomBallState * const>(ball_a->state()))
				goto cleanup;

			ball_a->velocity() = normal.reflect(ball_a->velocity());
			goto cleanup;

		} else if (paddle_a)
		{
			/* paddle vs everything \ { ball } */
			cout << "TODO: paddle vs bonus and stuff" << endl;
		}

		swap(a, b);
		swap(ball_a, ball_b);
		swap(brick_a, brick_b);
		swap(paddle_a, paddle_b);

		normal = -normal;
	}

cleanup:
	if (delete_a)
	{
		this->remove(a);
		delete a;
	}

	if (delete_b)
	{
		this->remove(b);
		delete b;
	}
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

bool BreakoutWorld::load_level(string level_filename_path)
{
	Json::Reader reader;
	Json::Value level;

	ifstream level_file(level_filename_path);
	string level_json
	(
		(istreambuf_iterator<char>(level_file)),
		istreambuf_iterator<char>()
	);

	bool parsingSuccessful = reader.parse(level_json, level);
	if (!parsingSuccessful)
		return false;

	Json::Value bricks = level["bricks"];
	Json::Value map = level["map"];
	Json::Value balls = level["balls"];

	if (!bricks || !bricks.isObject() || !map || !map.isArray() || !balls || !balls.isArray())
		return false;

	// vector<string> brick_types = bricks.getMemberNames();
	// for (unsigned int i = 0; i < brick_types.size(); i++)
	// {
	// 	string alias = brick_types[i];
	// 	string type = bricks[brick_types[i]]["type"].asString();
	// 	string color = bricks[brick_types[i]]["color"].asString();
	// 	unsigned int hits = bricks[brick_types[i]].get("hits", 1).asUInt();
	// }

	const string NO_BRICK = string(1, ' ');
	const string NORMAL_BRICK("normal");
	const string GLASS_BRICK("glass");
	const string CONCRETE_BRICK("concrete");

	const string NORMAL_BALL("normal");
	const string FIRE_BALL("fire");
	const string PHANTOM_BALL("phantom");

	const unsigned int X_BLOCKS = 19;
	const unsigned int Y_BLOCKS = 40;

	const double X_OFFSET = (BreakoutWorld::WIDTH - (X_BLOCKS - 1) * Brick::BASE_WIDTH) / 2;
	const double Y_OFFSET = (BreakoutWorld::HEIGHT - (Y_BLOCKS - 1) * Brick::BASE_HEIGHT) / 2;

	for (unsigned int i = 0; i < map.size(); i++)
	{
		string map_line = map[i].asString();

		unsigned int y = i * Brick::BASE_HEIGHT;

		for (unsigned int j = 0; j < map_line.length(); j++)
		{
			string brick_type_alias = string(1, map_line[j]);

			if (!brick_type_alias.compare(NO_BRICK))
				continue;

			unsigned int x = j * Brick::BASE_WIDTH;
			Point position = Point(X_OFFSET + x, Y_OFFSET + y);

			string brick_type = bricks[brick_type_alias]["type"].asString();
			if (!brick_type.compare(NORMAL_BRICK))
			{
				unsigned int hits = bricks[brick_type_alias].get("hits", 1).asUInt();
				string color = bricks[brick_type_alias].get("color", "white").asString();

				Brick *brick = BrickFactory::makeNormalBrick(position, QColor(color.c_str()), hits);
				this->add(brick);

			} else if (!brick_type.compare(GLASS_BRICK))
			{
				Brick *brick = BrickFactory::makeGlassBrick(position);
				this->add(brick);

			} else if (!brick_type.compare(CONCRETE_BRICK))
			{
				Brick *brick = BrickFactory::makeConcreteBrick(position);
				this->add(brick);

			} else
				return false;

		}
	}

	for (unsigned int i = 0; i < balls.size(); i++)
	{
		// unsigned int radius = balls[i].get("radius", DEFAULT_BALL_RADIUS).asUInt();
		// string color = balls[i]["color"].asString();

		double px = balls[i]["position"].get("x", 0.0).asDouble();
		double py = balls[i]["position"].get("y", 0.0).asDouble();

		double vx = balls[i]["velocity"].get("x", 0.0).asDouble();
		double vy = balls[i]["velocity"].get("y", 0.0).asDouble();

		if (vx == 0.0 && vy == 0.0)
		{
			std::default_random_engine generator;
			generator.seed(time(NULL));

			std::uniform_real_distribution<double> distribution(0, PI * 2);
			double angle = distribution(generator);

			vx = cos(angle) * Ball::BASE_VELOCITY;
			vy = sin(angle) * Ball::BASE_VELOCITY;
		}

		string ball_type = balls[i]["type"].asString();
		Point position(px, py);
		Vector velocity(vx, vy);

		if (!ball_type.compare(NORMAL_BALL))
		{
			Ball *ball = BallFactory::makeNormalBall(position, velocity);
			this->add(ball);

		} else if (!ball_type.compare(FIRE_BALL))
		{
			Ball *ball = BallFactory::makeFireBall(position, velocity);
			this->add(ball);

		} else if (!ball_type.compare(PHANTOM_BALL))
		{
			Ball *ball = BallFactory::makePhantomBall(position, velocity);
			this->add(ball);

		} else
			return false;
	}

	return true;
}

void BreakoutWorld::step(const double& dt)
{
	super::step(dt);

	set<Ball*>::iterator it = this->_balls.begin();
	set<Ball*>::iterator end = this->_balls.end();
	
	for (; it != end; it++)
	{
		if ((*it)->position().x() - (*it)->radius() <= 0)
			(*it)->velocity() = (*it)->velocity() = Vector(1, 0).reflect((*it)->velocity());

		else if ((*it)->position().x() + (*it)->radius() >= BreakoutWorld::WIDTH)
			(*it)->velocity() = (*it)->velocity() = Vector(-1, 0).reflect((*it)->velocity());

		bool delete_ball = false;

		if ((*it)->position().y() <= 0)
		{
			delete_ball = true;

			// TODO: SCORE
			cout << "SCORE 2" << endl;

		} else if ((*it)->position().y() >= BreakoutWorld::HEIGHT)
		{
			delete_ball = true;

			// TODO: SCORE
			cout << "SCORE 1" << endl;
		}

		if (delete_ball)
		{
			this->remove(*it);
			delete *it;
		}

	}
}