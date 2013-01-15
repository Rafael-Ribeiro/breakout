#include "../Brick.hpp"

const unsigned int Paddle::BASE_WIDTH = 64;
const unsigned int Paddle::BASE_HEIGHT = 10;
const double Paddle::VELOCITY = 400.0;

Paddle::Paddle(const Point &initial_position)
	: Box(Paddle::BASE_WIDTH, Paddle::BASE_HEIGHT), Movable(Vector(0, 0)), Drawable(), _player(NULL), state(NULL)
{
	this->init(initial_position);
}

Paddle::~Paddle()
{
	delete this->state;
}

Player* & Paddle::player()
{
	return this->_player;
}

Player* const & Paddle::player() const
{
	return this->_player;
}

void Paddle::set_state(PaddleState *state)
{
	delete this->state;

	this->state = state;
	state->set_paddle(this);
}

PaddleState const * Paddle::get_state() const
{
	return this->state;
}

void Paddle::draw(QPainter& painter) const
{
	this->state->draw(painter);
}

Paddle* PaddleFactory::makeNormalPaddle(const Point &initial_position)
{
	Paddle *paddle = new Paddle(initial_position);
	paddle->set_state(new NormalPaddleState());

	return paddle;
}
