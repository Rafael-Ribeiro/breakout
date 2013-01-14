#include "../common.hpp"

#include "../BallState.hpp"

BallState::~BallState()
{
}

void BallState::set_ball(Ball* ball)
{
	this->ball = ball;
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
