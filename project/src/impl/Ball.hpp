#include "../Ball.hpp"

const double Ball::BASE_RADIUS = 10.0;
const double Ball::DENSITY = 1;

void Ball::on_collision(Body &other, Contact &contact)
{
	/* TODO: Ball::on_collision */
}

void Ball::draw(QPainter& painter) const
{
	painter.drawEllipse
	(
		QPointF(this->position().x(), this->position().y()),
		this->radius(),
		this->radius()
	);
}
