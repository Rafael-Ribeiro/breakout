#include "../common.hpp"

#include "../BallState.hpp"

BallState::~BallState()
{
}

void BallState::set_ball(Ball* ball)
{
	this->ball = ball;
}

bool BallState::collision_filter(Body &other)
{
	/* collides with everything */
	MARKUSED(other);
	return true;
}

bool NormalBallState::collision_updates_physics(Body &other)
{
	/* TODO */
	return true;
}

bool NormalBallState::collision_handle(Contact &contact)
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

bool FireBallState::collision_updates_physics(Body &other)
{
	/* TODO */
	return true;
}

bool FireBallState::collision_handle(Contact &contact)
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

bool PhantomBallState::collision_updates_physics(Body &other)
{
	/* TODO */
	return true;
}

bool PhantomBallState::collision_handle(Contact &contact)
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
