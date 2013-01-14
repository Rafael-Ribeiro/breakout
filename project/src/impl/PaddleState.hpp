
#include "../PaddleState.hpp"

PaddleState::~PaddleState()
{
}

void PaddleState::set_paddle(Paddle* paddle)
{
	this->paddle = paddle;
}


bool PaddleState::collision_filter(Body &other)
{
	/* collides with everything */
	MARKUSED(other);
	return true;
}

bool NormalPaddleState::collision_updates_physics(Body &other)
{
	/* TODO */
	return true;
}

bool NormalPaddleState::collision_handle(Contact &contact)
{
	return false;
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
