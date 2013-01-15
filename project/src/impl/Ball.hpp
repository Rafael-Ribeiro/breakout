#include "../Ball.hpp"

#include "../Player.hpp"

const double Ball::BASE_RADIUS = 10.0;
const double Ball::MAX_RADIUS = 20.0;
const double Ball::BASE_VELOCITY = 300.0;

Ball::Ball(const Point &initial_position, const Vector &initial_velocity)
	: Circle(Ball::BASE_RADIUS), Movable(initial_velocity), Drawable(), _state(NULL), _last_player(NULL)
{
	this->init(initial_position);
}

Ball::~Ball()
{
	delete this->_state;
}

void Ball::set_state(BallState *state)
{
	delete this->_state;

	this->_state = state;
	state->set_ball(this);
}

BallState * const & Ball::state() const
{
	return this->_state;
}

Player * const & Ball::last_player() const
{
	return this->_last_player;
}

void Ball::draw(QPainter& painter) const
{
	this->_state->draw(painter);
}

void Ball::hit(Player& player)
{
	this->_last_player = &player;
}

void Ball::grow()
{
	this->radius() = min(Ball::MAX_RADIUS, this->radius() * 1.5);
}

Ball* BallFactory::make_normal_ball(const Point &initial_position, const Vector &initial_velocity)
{
	Ball *ball = new Ball(initial_position, initial_velocity);
	ball->set_state(new NormalBallState());
	
	return ball;
}

Ball* BallFactory::make_fire_ball(const Point &initial_position, const Vector &initial_velocity)
{
	Ball *ball = new Ball(initial_position, initial_velocity);
	ball->set_state(new FireBallState());

	return ball;
}

Ball* BallFactory::make_phantom_ball(const Point &initial_position, const Vector &initial_velocity)
{
	Ball *ball = new Ball(initial_position, initial_velocity);
	ball->set_state(new PhantomBallState());

	return ball;
}