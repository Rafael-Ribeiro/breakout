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

void Paddle::set_state(PaddleState *state)
{
	delete this->state;

	this->state = state;
	state->set_paddle(this);
}

bool Paddle::collision_filter(Body &other)
{
	return this->state->collision_filter(other);
}

bool Paddle::collision_updates_physics(Body &other)
{
	return this->state->collision_updates_physics(other);
}

bool Paddle::collision_handle(Contact &contact)
{
	return this->state->collision_handle(contact);
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
