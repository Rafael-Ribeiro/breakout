#include "../Paddle.hpp"

const double Paddle::INITIAL_WIDTH = 50.0;
const double Paddle::INITIAL_HEIGHT = 10.0;

bool Paddle::pre_collision(Body &other)
{
	/* TODO: Ball::on_collision */
	return true;
}

bool Paddle::post_collision(Contact &contact)
{
	MARKUSED(contact);
	return false;
}


void Paddle::draw(QPainter& painter) const
{ 
	painter.setBrush(QBrush(Qt::white));
	painter.setPen(Qt::red);

	painter.drawRect
	(
		this->position().x() - this->width() / 2,
		this->position().y() - this->height() / 2,
		this->width(),
		this->height()
	);
}
