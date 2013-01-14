#include "../BallState.hpp"

BallState::~BallState()
{
}

void BallState::setBall(Ball* ball)
{
	this->ball = ball;
}

bool NormalBallState::pre_collision(Body &other)
{
	/* TODO: Ball::on_collision */
	return true;
}

bool NormalBallState::post_collision(Contact &contact)
{
	this->ball->velocity() = contact.normal().reflect(this->ball->velocity());
	return false;
}

void NormalBallState::draw(QPainter& painter) const
{
	painter.setBrush(QBrush(Qt::white));
	painter.setPen(Qt::white);
	
	painter.drawEllipse
	(
		QPointF(this->ball->position().x(), this->ball->position().y()),
		this->ball->radius() - 0.5, /* half stroke width */
		this->ball->radius() - 0.5
	);
}

bool FireBallState::pre_collision(Body &other)
{
	/* TODO: Ball::on_collision */
	return true;
}

bool FireBallState::post_collision(Contact &contact)
{
	this->ball->velocity() = contact.normal().reflect(this->ball->velocity());
	return false;
}

void FireBallState::draw(QPainter& painter) const
{
	painter.setBrush(QBrush(QColor(0xff, 0x66, 0x00)));
	painter.setPen(Qt::red);

	painter.drawEllipse
	(
		QPointF(this->ball->position().x(), this->ball->position().y()),
		this->ball->radius() - 0.5, /* half stroke width */
		this->ball->radius() - 0.5
	);
}

bool PhantomBallState::pre_collision(Body &other)
{
	/* TODO: Ball::on_collision */
	return true;
}

bool PhantomBallState::post_collision(Contact &contact)
{
	this->ball->velocity() = contact.normal().reflect(this->ball->velocity());
	return false;
}

void PhantomBallState::draw(QPainter& painter) const
{
	painter.setBrush(QBrush(QColor(0xff, 0xff, 0xff, 0xcc)));
	painter.setPen(Qt::white);

	painter.drawEllipse
	(
		QPointF(this->ball->position().x(), this->ball->position().y()),
		this->ball->radius() - 0.5, /* half stroke width */
		this->ball->radius() - 0.5
	);
}
