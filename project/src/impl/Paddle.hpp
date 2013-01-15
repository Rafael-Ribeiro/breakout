#include "../Brick.hpp"

const unsigned int Paddle::BASE_WIDTH = 64;
const unsigned int Paddle::BASE_HEIGHT = 10;

Paddle::Paddle(const Point &initial_position)
	: Box(Paddle::BASE_WIDTH, Paddle::BASE_HEIGHT), Movable(Vector(0, 0)), Drawable(), player(NULL), state(NULL)
{
	this->init(initial_position);
}

Paddle::~Paddle()
{
	delete this->state;
}

void Paddle::set_player(Player *player)
{
	assert(!this->player);
	this->player = player;
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
