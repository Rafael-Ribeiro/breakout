#include "../BreakoutFrame.hpp"

#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>

#include "../Keyboard.hpp"

BreakoutFrame::BreakoutFrame(const BreakoutWorld *world, QWidget *parent)
	: super(parent), world(world)
{
	this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
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
	return QApplication::desktop()->size();
//	return QSize(BreakoutWorld::WIDTH, BreakoutWorld::HEIGHT);
}

void BreakoutFrame::keyPressEvent(QKeyEvent * event)
{
	Keyboard::get_instance().handle_event(event, true);
}

void BreakoutFrame::keyReleaseEvent(QKeyEvent * event)
{
	// FIXME
	if (event->key() == Qt::Key::Key_Escape)
		exit(0);

	Keyboard::get_instance().handle_event(event, false);
}

void BreakoutFrame::paintEvent(QPaintEvent *event)
{
	super::paintEvent(event);

	QPainter painter(this);



	unsigned int dx = (this->width() - BreakoutWorld::WIDTH) / 2;
	unsigned int dy = (this->height() - BreakoutWorld::HEIGHT) / 2;

	painter.setBackground(QColor(0xDD, 0xDD, 0xDD));
	painter.eraseRect(this->rect());

	painter.setBackground(QColor(0xEE, 0xEE, 0xEE));
	painter.eraseRect(QRect(dx, 0, BreakoutWorld::WIDTH, this->height()));

	painter.translate(dx, dy);
	set<Drawable*>::const_iterator it = this->world->drawables().begin();
	set<Drawable*>::const_iterator end = this->world->drawables().end();

	for (; it != end; it++)
		(*it)->draw(painter);
}