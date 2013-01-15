#include "../Brick.hpp"

const unsigned int Paddle::BASE_WIDTH = 64;
const unsigned int Paddle::BASE_HEIGHT = 10;
const double Paddle::VELOCITY = 600.0;

Paddle::Paddle(const Point &initial_position)
	: Box(Paddle::BASE_WIDTH, Paddle::BASE_HEIGHT), Movable(Vector(0, 0)), Drawable(), _player(NULL), _state(NULL)
{
	this->init(initial_position);
}

Paddle::~Paddle()
{
	delete this->_state;
}

void Paddle::player(Player *player)
{
	this->_player = player;
}

Player* const & Paddle::player() const
{
	return this->_player;
}

void Paddle::set_state(PaddleState *state)
{
	delete this->_state;

	this->_state = state;
	state->set_paddle(this);
}

PaddleState * const & Paddle::state() const
{
	return this->_state;
}

void Paddle::draw(QPainter& painter) const
{
	this->_state->draw(painter);
}

Paddle* PaddleFactory::make_normal_paddle(const Point &initial_position)
{
	Paddle *paddle = new Paddle(initial_position);
	paddle->set_state(new NormalPaddleState());

	return paddle;
}
