#include "../common.hpp"

#include "../BrickState.hpp"

BrickState::~BrickState()
{
}

void BrickState::set_brick(Brick* brick)
{
	this->brick = brick;
}

NormalBrickState::NormalBrickState(QColor color, unsigned int hits)
	: _color(color), _hits(hits), _remaining(hits)
{	
}

bool NormalBrickState::hit()
{
	this->_remaining--;
	return this->_remaining == 0;
}

void NormalBrickState::draw(QPainter& painter) const
{
	QColor brush_color = this->_color.darker(100 + (this->_hits - this->_remaining) * 50);
	QColor pen_color = brush_color.darker(150);

	painter.setBrush(QBrush(brush_color));
	painter.setPen(pen_color);

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
	QColor brush_color(0x40, 0x70, 0xFE, 0x55);
	QColor pen_color = brush_color.darker(150);

	painter.setBrush(QBrush(brush_color));
	painter.setPen(pen_color);

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
	QColor brush_color(0xB8, 0xB8, 0xB8);
	QColor pen_color = brush_color.darker(150);

	painter.setBrush(QBrush(brush_color));
	painter.setPen(pen_color);

	painter.drawRect
	(
		this->brick->position().x() - this->brick->hwidth() + 0.5,
		this->brick->position().y() - this->brick->hheight() + 0.5,
		this->brick->width() - 1,
		this->brick->height() -1
	);
}
