#include "../common.hpp"

#include "../BrickState.hpp"

BrickState::~BrickState()
{
}

void BrickState::set_brick(Brick* brick)
{
	this->brick = brick;
}

NormalBrickState::NormalBrickState(unsigned int hits)
	: hits(hits)
{	
}

bool NormalBrickState::hit()
{
	this->hits--;
	return this->hits == 0;
}

void NormalBrickState::draw(QPainter& painter) const
{
	painter.setBrush(QBrush(Qt::white));
	painter.setPen(Qt::red);

	painter.drawRect
	(
		this->brick->position().x() - this->brick->hwidth() + 0.5,
		this->brick->position().y() - this->brick->hheight() + 0.5,
		this->brick->width() - 1,
		this->brick->height() -1
	);
}

bool GlassBrickState::hit()
{
	return true;
}

void GlassBrickState::draw(QPainter& painter) const
{
	painter.setBrush(QBrush(Qt::blue));
	painter.setPen(Qt::white);

	painter.drawRect
	(
		this->brick->position().x() - this->brick->hwidth() + 0.5,
		this->brick->position().y() - this->brick->hheight() + 0.5,
		this->brick->width() - 1,
		this->brick->height() -1
	);
}

bool ConcreteBrickState::hit()
{
	return false;
}

void ConcreteBrickState::draw(QPainter& painter) const
{
	const QColor gray(0xcc, 0xcc, 0xcc);

	painter.setBrush(QBrush(gray));
	painter.setPen(gray);

	painter.drawRect
	(
		this->brick->position().x() - this->brick->hwidth() + 0.5,
		this->brick->position().y() - this->brick->hheight() + 0.5,
		this->brick->width() - 1,
		this->brick->height() -1
	);
}
