#include "../BreakoutFrame.hpp"

#include <QPainter>

const unsigned int BreakoutFrame::WIDTH = 1024;
const unsigned int BreakoutFrame::HEIGHT = 768;

BreakoutFrame::BreakoutFrame(const Engine *engine, QWidget *parent)
	: super(parent), engine(engine)
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
	return QSize(BreakoutFrame::WIDTH, BreakoutFrame::HEIGHT);
}

void BreakoutFrame::paintEvent(QPaintEvent *event)
{
	super::paintEvent(event);

	QPainter painter(this);

	set<Body*>::const_iterator it = this->engine->bodies().begin();
	set<Body*>::const_iterator end = this->engine->bodies().end();

	for (; it != end; it++)
	{
		Drawable* drawable = dynamic_cast<Drawable*>(*it);
		if (!drawable)
			continue;

		drawable->draw(painter);
	}
}