#include <fstream>
#include <sys/time.h>

#include "jsoncpp/inc/json.h"
#include "CPUStrategyMultiton.hpp"

#include "../BreakoutWorld.hpp"

const unsigned int BreakoutWorld::WIDTH = 1024;
const unsigned int BreakoutWorld::HEIGHT = 768;

const unsigned int BreakoutWorld::GOAL_SCORE = 100;
const unsigned int BreakoutWorld::BONUS_SCORE = 25;
const unsigned int BreakoutWorld::BRICK_SCORE = 5;

BreakoutWorld::BreakoutWorld() : World()
{
	Paddle *player_1_paddle = PaddleFactory::make_normal_paddle(Point(512, 748));
	this->add(player_1_paddle);

	Paddle *player_2_paddle = PaddleFactory::make_normal_paddle(Point(512, 20));
	this->add(player_2_paddle);

	HumanPlayer *human_player = new HumanPlayer(player_1_paddle);
	this->_players[0] = human_player;

	human_player = new HumanPlayer(player_2_paddle, Qt::Key::Key_A, Qt::Key::Key_D);
	this->_players[1] = human_player;

	// CPUPlayer *cpu_player = new CPUPlayer(player_2_paddle, &CPUStrategyMultiton::get_closest_ball_cpu_strategy_instance());
	// this->_players[1] = cpu_player;

	// CPUPlayer *cpu_player = new CPUPlayer(player_2_paddle, &CPUStrategyMultiton::get_first_ball_cpu_strategy_instance());
	// this->_players[1] = cpu_player;

	// cpu_player = new CPUPlayer(player_1_paddle, &CPUStrategyMultiton::get_closest_ball_cpu_strategy_instance());
	// this->_players[0] = cpu_player;

	this->restart();
}

void BreakoutWorld::add(Body *body)
{
	super::add(body);

	Drawable* drawable = dynamic_cast<Drawable*>(body);
	if (drawable)
		this->_drawables.insert(drawable);

	Ball* ball = dynamic_cast<Ball*>(body);
	if (ball)
		this->_balls.insert(ball);

	Brick* brick = dynamic_cast<Brick*>(body);
	if (brick)
		this->_bricks.insert(brick);

	Paddle* paddle = dynamic_cast<Paddle*>(body);
	if (paddle)
		this->_paddles.insert(paddle);

	Bonus* bonus = dynamic_cast<Bonus*>(body);
	if (bonus)
		this->_bonuses.insert(bonus);

}

void BreakoutWorld::remove(Body *body)
{
	super::remove(body);

	Drawable* drawable = dynamic_cast<Drawable*>(body);
	if (drawable)
		this->_drawables.erase(drawable);

	Ball* ball = dynamic_cast<Ball*>(body);
	if (ball)
		this->_balls.erase(ball);

	Brick* brick = dynamic_cast<Brick*>(body);
	if (brick)
		this->_bricks.erase(brick);

	Paddle* paddle = dynamic_cast<Paddle*>(body);
	if (paddle)
		this->_paddles.erase(paddle);

	Bonus* bonus = dynamic_cast<Bonus*>(body);
	if (bonus)
		this->_bonuses.erase(bonus);
}

void BreakoutWorld::clear()
{
	while (!this->_balls.empty())
	{
		Body *b = *this->_balls.begin();
		this->remove(b);
		delete b;
	}

	while (!this->_bricks.empty())
	{
		Body *b = *this->_bricks.begin();
		this->remove(b);
		delete b;
	}

	while (!this->_bonuses.empty())
	{
		Body *b = *this->_bonuses.begin();
		this->remove(b);

		delete b;
	}
}

void BreakoutWorld::restart()
{
	this->clear();

	for (unsigned int i = 0; i < 2; i++)
		this->_players[i]->restart();

	this->load_level("../levels/level1.json");
}

bool BreakoutWorld::collision_filter(Body &a, Body &b)
{
	Ball* ball_a = dynamic_cast<Ball*>(&a);
	Ball* ball_b = dynamic_cast<Ball*>(&b);
	
	Bonus* bonus_a = dynamic_cast<Bonus*>(&a);
	Bonus* bonus_b = dynamic_cast<Bonus*>(&b);

	Paddle* paddle_a = dynamic_cast<Paddle*>(&a);
	Paddle* paddle_b = dynamic_cast<Paddle*>(&b);
	
	/* balls collide with all objects except */
	if (ball_a || ball_b)
	{
		/* bonuses */
		if (bonus_a || bonus_b)
			return false;

		return true;
	}

	/* paddles collides with bonuses (and balls ^) */
	if ((paddle_a && bonus_b) || (paddle_b && bonus_a))
		return true;

	return false;
}

bool BreakoutWorld::collision_updates_physics(Body &a, Body &b)
{
	Ball* ball_a = dynamic_cast<Ball*>(&a);
	Ball* ball_b = dynamic_cast<Ball*>(&b);
	
	Brick* brick_a = dynamic_cast<Brick*>(&a);
	Brick* brick_b = dynamic_cast<Brick*>(&b);

	Bonus* bonus_a = dynamic_cast<Bonus*>(&a);
	Bonus* bonus_b = dynamic_cast<Bonus*>(&b);

	Paddle* paddle_a = dynamic_cast<Paddle*>(&a);
	Paddle* paddle_b = dynamic_cast<Paddle*>(&b);

	for (unsigned int i = 0; i < 2; i++)
	{
		if (ball_a)
		{
			/* ball vs everything */
			if (ball_b || paddle_b)
				return true;

			if (bonus_b)
				return false;

			assert(brick_b);

			if (dynamic_cast<ConcreteBrickState * const>(brick_b->state()))
				return true;

			if (dynamic_cast<GlassBrickState * const>(brick_b->state()) || dynamic_cast<PhantomBallState * const>(ball_a))
				return false;

			return true;
		} else if (paddle_a)
		{
			if (bonus_b)
				return true;
		}

		swap(ball_a, ball_b);
		swap(brick_a, brick_b);
		swap(paddle_a, paddle_b);
		swap(bonus_a, bonus_b);
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

	Bonus* bonus_a = dynamic_cast<Bonus*>(a);
	Bonus* bonus_b = dynamic_cast<Bonus*>(b);

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
				double velocity = ball_a->velocity().length();

				Vector dp = ball_a->position() - paddle_b->position();

				double vy = ball_a->velocity().y() > 0 ? -1 : 1;
				double vx = dp.x() / paddle_b->width() * 2;

				ball_a->velocity() = Vector(vx, vy).normalize() * velocity;
				ball_a->hit(*paddle_b->player());

				/* push the ball */
				ball_a->position() += paddle_b->velocity() * -contact.toc();

				goto cleanup;
			}

			assert(brick_b);

			bool phantom = dynamic_cast<PhantomBallState * const>(ball_a->state());
			bool fire = dynamic_cast<FireBallState * const>(ball_a->state());
			bool concrete = dynamic_cast<ConcreteBrickState * const>(brick_b->state());

			bool glass = dynamic_cast<GlassBrickState * const>(brick_b->state());

			if (fire)
				delete_b = brick_b->hit_all();
			else
				delete_b = brick_b->hit_once();			

			if (phantom && !concrete)
				delete_b = true;

			if (delete_b && ball_a->last_player())
			{
				Vector velocity = (ball_a->last_player()->paddle()->position() - brick_b->position()).normalize() * Bonus::BASE_VELOCITY;

				ball_a->last_player()->add_score(BreakoutWorld::BRICK_SCORE);

				if (random_int(0, 3) == 0)
					this->add(BonusFactory::make_random_bonus(brick_b->position(), velocity));
			}

			if (glass || (phantom && !concrete))
				goto cleanup;

			ball_a->velocity() = normal.reflect(ball_a->velocity());
			goto cleanup;

		} else if (paddle_a)
		{
			if (bonus_b)
			{
				paddle_a->player()->redeem(*bonus_b, *this);
				paddle_a->player()->add_score(BreakoutWorld::BONUS_SCORE);

				delete_b = true;

				goto cleanup;
			}
		}

		swap(a, b);
		swap(ball_a, ball_b);
		swap(brick_a, brick_b);
		swap(bonus_a, bonus_b);
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

const set<Bonus*>& BreakoutWorld::bonuses() const
{
	return this->_bonuses;
}

const set<Drawable*>& BreakoutWorld::drawables() const
{
	return this->_drawables;
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

				Brick *brick = BrickFactory::make_normal_brick(position, QColor(color.c_str()), hits);
				this->add(brick);

			} else if (!brick_type.compare(GLASS_BRICK))
			{
				Brick *brick = BrickFactory::make_glass_brick(position);
				this->add(brick);

			} else if (!brick_type.compare(CONCRETE_BRICK))
			{
				Brick *brick = BrickFactory::make_concrete_brick(position);
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

		Vector velocity;
		if (vx == 0.0 && vy == 0.0)
			velocity = Vector::random_unitary() * Ball::BASE_VELOCITY;
		else
			velocity = Vector(vx, vy);

		if (!ball_type.compare(NORMAL_BALL))
		{
			Ball *ball = BallFactory::make_normal_ball(position, velocity);
			this->add(ball);

		} else if (!ball_type.compare(FIRE_BALL))
		{
			Ball *ball = BallFactory::make_fire_ball(position, velocity);
			this->add(ball);

		} else if (!ball_type.compare(PHANTOM_BALL))
		{
			Ball *ball = BallFactory::make_phantom_ball(position, velocity);
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
	
	while (it != this->_balls.end())
	{
		if ((*it)->position().x() - (*it)->radius() <= 0)
		{
			(*it)->velocity() = (*it)->velocity() = Vector(1, 0).reflect((*it)->velocity());
			(*it)->position().x() = (*it)->radius() + numeric_limits<double>::epsilon();

		} else if ((*it)->position().x() + (*it)->radius() >= BreakoutWorld::WIDTH)
		{
			(*it)->velocity() = (*it)->velocity() = Vector(-1, 0).reflect((*it)->velocity());
			(*it)->position().x() = BreakoutWorld::WIDTH - (*it)->radius() - numeric_limits<double>::epsilon();
		}

		bool delete_ball = false;

		set<Ball*>::iterator prev = it;
		it++;

		if ((*prev)->position().y() <= 0)
		{
			delete_ball = true;
			this->_players[1]->add_score(BreakoutWorld::GOAL_SCORE);

		} else if ((*prev)->position().y() >= BreakoutWorld::HEIGHT)
		{
			delete_ball = true;
			this->_players[0]->add_score(BreakoutWorld::GOAL_SCORE);
		}

		if (delete_ball)
		{
			this->remove(*prev);
			delete *prev;
		}

	}
	
	set<Bonus*>::iterator it_bonus = this->_bonuses.begin();
	
	while (it_bonus != this->_bonuses.end())
	{
		set<Bonus*>::iterator prev = it_bonus;
		it_bonus++;

		if ((*prev)->position().y() < 0 || (*prev)->position().y() > BreakoutWorld::HEIGHT)
		{

			this->remove(*prev);
			delete *prev;
		}
	}

	for (unsigned int i = 0; i < 2; i++)
	{
		this->_players[i]->step(*this, dt);

		double x_correction = 0;
		if (this->_players[i]->paddle()->left() < 0)
			x_correction = -this->_players[i]->paddle()->left();

		else if (this->_players[i]->paddle()->right() > BreakoutWorld::WIDTH)
			x_correction = BreakoutWorld::WIDTH - this->_players[i]->paddle()->right();

		if (x_correction != 0)
		{
			this->_players[i]->paddle()->position() += Vector(x_correction, 0);
			this->_players[i]->paddle()->velocity() = Vector(0, 0);
		}
	}

	if (this->_balls.size() == 0)
		this->restart();

}