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

void Ball::set_state(BallState *state)
{
	delete this->state;

	this->state = state;
	state->set_ball(this);
}

bool Ball::collision_filter(Body &other)
{
	return this->state->collision_filter(other);
}

bool Ball::collision_updates_physics(Body &other)
{
	return this->state->collision_updates_physics(other);
}

bool Ball::collision_handle(Contact &contact)
{
	return this->state->collision_handle(contact);
}

void Ball::draw(QPainter& painter) const
{
	this->state->draw(painter);
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