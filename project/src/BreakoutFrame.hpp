#pragma once

#include <QFrame>

#include "BreakoutWorld.hpp"

class BreakoutFrame
	: public QFrame
{
	Q_OBJECT

public:
	typedef QFrame super;
	BreakoutFrame(const BreakoutWorld *world, QWidget *parent = NULL);

private:
	const BreakoutWorld* world;

public:
	void updateSize();
	QSize sizeHint() const;
	
	void paintEvent(QPaintEvent *event);
};