#pragma once

#include <QFrame>

#include "Engine.hpp"

class BreakoutFrame
	: public QFrame
{
	Q_OBJECT

public:
	typedef QFrame super;
	static const unsigned int WIDTH;
	static const unsigned int HEIGHT;

	BreakoutFrame(const Engine *engine, QWidget *parent = NULL);

private:
	const Engine* engine;

public:
	void updateSize();
	QSize sizeHint() const;
	
	void paintEvent(QPaintEvent *event);
};