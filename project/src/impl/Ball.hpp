#include "../Ball.hpp"

#include "../Player.hpp"

const double Ball::BASE_RADIUS = 10.0;
const double Ball::BASE_VELOCITY = 300.0;

Ball::Ball(const Point &initial_position, const Vector &initial_velocity)
	: Circle(Ball::BASE_RADIUS), Movable(initial_velocity), Drawable(), _state(NULL)
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

void Ball::draw(QPainter& painter) const
{
	this->_state->draw(painter);
}

Ball* BallFactory::makeNormalBall(const Point &initial_position, const Vector &initial_velocity)
{
	Ball *ball = new Ball(initial_position, initial_velocity);
	ball->set_state(new NormalBallState());
	
	return ball;
}

Ball* BallFactory::makeFireBall(const Point &initial_position, const Vector &initial_velocity)
{
	Ball *ball = new Ball(initial_position, initial_velocity);
	ball->set_state(new FireBallState());

	return ball;
}

Ball* BallFactory::makePhantomBall(const Point &initial_position, const Vector &initial_velocity)
{
	Ball *ball = new Ball(initial_position, initial_velocity);
	ball->set_state(new PhantomBallState());

	return ball;
}