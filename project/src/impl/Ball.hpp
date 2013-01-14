#include "../Ball.hpp"

const double Ball::BASE_RADIUS = 10.0;

Ball::Ball(const Point &initial_position, const Vector &initial_velocity)
	: Circle(Ball::BASE_RADIUS), Movable(initial_velocity), Drawable(), state(NULL)
{
	this->init(initial_position);
}

Ball::~Ball()
{
	delete this->state;
}

bool Ball::pre_collision(Body &other)
{
	return this->state->pre_collision(other);
}

bool Ball::post_collision(Contact &contact)
{
	return this->state->post_collision(contact);
}

void Ball::draw(QPainter& painter) const
{
	this->state->draw(painter);
}

void Ball::setState(BallState *state)
{
	delete this->state;

	this->state = state;
	state->setBall(this);
}

Ball* BallFactory::makeNormalBall(const Point &initial_position, const Vector &initial_velocity)
{
	Ball *ball = new Ball(initial_position, initial_velocity);
	ball->setState(new NormalBallState());

	return ball;
}

Ball* BallFactory::makeFireBall(const Point &initial_position, const Vector &initial_velocity)
{
	Ball *ball = new Ball(initial_position, initial_velocity);
	ball->setState(new FireBallState());

	return ball;
}

Ball* BallFactory::makePhantomBall(const Point &initial_position, const Vector &initial_velocity)
{
	Ball *ball = new Ball(initial_position, initial_velocity);
	ball->setState(new PhantomBallState());

	return ball;
}