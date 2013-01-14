#include "../Brick.hpp"

const unsigned int Brick::BASE_WIDTH = 48;
const unsigned int Brick::BASE_HEIGHT = 16;

Brick::Brick(const Point &initial_position)
	: Box(Brick::BASE_WIDTH, Brick::BASE_HEIGHT), Drawable(), state(NULL)
{
	this->init(initial_position);
}

Brick::~Brick()
{
	delete this->state;
}

bool Brick::pre_collision(Body &other)
{
	return this->state->pre_collision(other);
}

bool Brick::post_collision(Contact &contact)
{
	return this->state->post_collision(contact);
}

void Brick::draw(QPainter& painter) const
{
	this->state->draw(painter);
}

void Brick::setState(BrickState *state)
{
	delete this->state;

	this->state = state;
	state->setBrick(this);
}

Brick* BrickFactory::makeNormalBrick(const Point &initial_position, unsigned int hits)
{
	Brick *brick = new Brick(initial_position);
	brick->setState(new NormalBrickState(hits));

	return brick;
}

Brick* BrickFactory::makeGlassBrick(const Point &initial_position)
{
	Brick *brick = new Brick(initial_position);
	brick->setState(new GlassBrickState());

	return brick;
}

Brick* BrickFactory::makeConcreteBrick(const Point &initial_position)
{
	Brick *brick = new Brick(initial_position);
	brick->setState(new ConcreteBrickState());

	return brick;
}