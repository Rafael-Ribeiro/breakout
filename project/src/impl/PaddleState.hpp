
#include "../PaddleState.hpp"

PaddleState::~PaddleState()
{
}

void PaddleState::set_paddle(Paddle* paddle)
{
	this->paddle = paddle;
}

void NormalPaddleState::draw(QPainter& painter) const
{
	painter.setBrush(QBrush(Qt::white));
	painter.setPen(Qt::red);

	painter.drawRect
	(
		this->paddle->position().x() - this->paddle->hwidth() + 0.5,
		this->paddle->position().y() - this->paddle->hheight() + 0.5,
		this->paddle->width() - 1,
		this->paddle->height() - 1
	);
}
