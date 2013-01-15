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
	QColor color_brush(0x4A, 0x4A, 0x4A);
	QColor color_pen = color_brush.darker(150);

	painter.setBrush(color_brush);
	painter.setPen(color_pen);
	
	painter.drawEllipse
	(
		QPointF(this->ball->position().x(), this->ball->position().y()),
		this->ball->radius() - 0.5, /* half stroke width */
		this->ball->radius() - 0.5
	);
}

void FireBallState::draw(QPainter& painter) const
{
	QColor color_brush(0xEB, 0x22, 0x22);
	QColor color_pen(0xEB, 0x72, 0x22);

	painter.setBrush(color_brush);
	painter.setPen(color_pen);
	
	painter.drawEllipse
	(
		QPointF(this->ball->position().x(), this->ball->position().y()),
		this->ball->radius() - 0.5, /* half stroke width */
		this->ball->radius() - 0.5
	);
}

void PhantomBallState::draw(QPainter& painter) const
{
	QColor color_brush(0x4A, 0x4A, 0x4A, 0x55);
	QColor color_pen = color_brush.darker(150);

	painter.setBrush(color_brush);
	painter.setPen(color_pen);
	
	painter.drawEllipse
	(
		QPointF(this->ball->position().x(), this->ball->position().y()),
		this->ball->radius() - 0.5, /* half stroke width */
		this->ball->radius() - 0.5
	);
}
