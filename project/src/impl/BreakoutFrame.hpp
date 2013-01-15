#include "../BreakoutFrame.hpp"

#include <QPainter>

BreakoutFrame::BreakoutFrame(const BreakoutWorld *world, QWidget *parent)
	: super(parent), world(world)
{
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	this->updateSize();
}

void BreakoutFrame::updateSize()
{
	QSize size = this->sizeHint();

	this->setMinimumSize(size);
	this->setMaximumSize(size);
	this->updateGeometry();
}

QSize BreakoutFrame::sizeHint() const
{
	return QSize(BreakoutWorld::WIDTH, BreakoutWorld::HEIGHT);
}

void BreakoutFrame::paintEvent(QPaintEvent *event)
{
	super::paintEvent(event);

	QPainter painter(this);

//	painter.setBackground(Qt::black);
	painter.eraseRect(this->rect());

	set<Body*>::const_iterator it = this->world->bodies().begin();
	set<Body*>::const_iterator end = this->world->bodies().end();

	for (; it != end; it++)
	{
		Drawable* drawable = dynamic_cast<Drawable*>(*it);
		if (!drawable)
		{
			continue;
		}
		drawable->draw(painter);
	}
}