#include "../Brick.hpp"

const unsigned int Paddle::BASE_WIDTH = 64;
const unsigned int Paddle::BASE_HEIGHT = 10;

Paddle::Paddle(const Point &initial_position)
	: Box(Paddle::BASE_WIDTH, Paddle::BASE_HEIGHT), Movable(Vector(0, 0)), Drawable(), state(NULL)
{
	this->init(initial_position);
}

Paddle::~Paddle()
{
	delete this->state;
}

bool Paddle::pre_collision(Body &other)
{
	return this->state->pre_collision(other);
}

bool Paddle::post_collision(Contact &contact)
{
	return this->state->post_collision(contact);
}

void Paddle::draw(QPainter& painter) const
{
	this->state->draw(painter);
}

void Paddle::setState(PaddleState *state)
{
	delete this->state;

	this->state = state;
	state->setPaddle(this);
}

Paddle* PaddleFactory::makeNormalPaddle(const Point &initial_position)
{
	Paddle *paddle = new Paddle(initial_position);
	paddle->setState(new NormalPaddleState());

	return paddle;
}