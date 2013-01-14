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

void Brick::set_state(BrickState *state)
{
	delete this->state;

	this->state = state;
	state->set_brick(this);
}

BrickState const * Brick::get_state() const
{
	return this->state;
}

void Brick::draw(QPainter& painter) const
{
	this->state->draw(painter);
}

bool Brick::hit()
{
	return this->state->hit();
}

Brick* BrickFactory::makeNormalBrick(const Point &initial_position, unsigned int hits)
{
	Brick *brick = new Brick(initial_position);
	brick->set_state(new NormalBrickState(hits));

	return brick;
}

Brick* BrickFactory::makeGlassBrick(const Point &initial_position)
{
	Brick *brick = new Brick(initial_position);
	brick->set_state(new GlassBrickState());

	return brick;
}

Brick* BrickFactory::makeConcreteBrick(const Point &initial_position)
{
	Brick *brick = new Brick(initial_position);
	brick->set_state(new ConcreteBrickState());

	return brick;
}