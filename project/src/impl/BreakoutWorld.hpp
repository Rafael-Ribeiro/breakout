#include <fstream>

#include "jsoncpp/inc/json.h"

#include "../BreakoutWorld.hpp"

BreakoutWorld::BreakoutWorld() : World()
{
	this->load_level("../levels/level1.json");
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

	const double X_OFFSET = (BreakoutFrame::WIDTH - (X_BLOCKS - 1) * Brick::BASE_WIDTH) / 2;
	const double Y_OFFSET = (BreakoutFrame::HEIGHT - (Y_BLOCKS - 1) * Brick::BASE_HEIGHT) / 2;

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

				Brick *brick = BrickFactory::makeNormalBrick(position, hits);
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