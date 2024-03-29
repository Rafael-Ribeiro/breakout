#include "../Brick.hpp"

const unsigned int Brick::BASE_WIDTH = 48;
const unsigned int Brick::BASE_HEIGHT = 16;

Brick::Brick(const Point &initial_position)
	: Box(Brick::BASE_WIDTH, Brick::BASE_HEIGHT), Drawable(), _state(NULL)
{
	this->init(initial_position);
}

Brick * Brick::clone()
{
	Brick * brick = new Brick(this->position());
	brick->set_state(this->_state->clone());

	return brick;
}

Brick::~Brick()
{
	delete this->_state;
}

void Brick::set_state(BrickState *state)
{
	delete this->_state;

	this->_state = state;
	state->set_brick(this);
}

BrickState * const & Brick::state() const
{
	return this->_state;
}

void Brick::draw(QPainter& painter) const
{
	this->_state->draw(painter);
}

bool Brick::hit_once()
{
	return this->_state->hit_once();
}

bool Brick::hit_all()
{
	return this->_state->hit_all();
}

Brick* BrickFactory::make_normal_brick(const Point &initial_position, QColor color, unsigned int hits)
{
	Brick *brick = new Brick(initial_position);
	brick->set_state(new NormalBrickState(color, hits));

	return brick;
}

Brick* BrickFactory::make_glass_brick(const Point &initial_position)
{
	Brick *brick = new Brick(initial_position);
	brick->set_state(new GlassBrickState());

	return brick;
}

Brick* BrickFactory::make_concrete_brick(const Point &initial_position)
{
	Brick *brick = new Brick(initial_position);
	brick->set_state(new ConcreteBrickState());

	return brick;
}