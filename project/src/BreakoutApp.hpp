#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>

#include <sys/time.h>

#include "BreakoutWorld.hpp"
#include "BreakoutFrame.hpp"

class BreakoutApp
	: public QWidget
{
	Q_OBJECT

public:
	typedef QWidget super;
	BreakoutApp(QWidget *parent = NULL);

private:
	BreakoutWorld world;
	QVBoxLayout layout;
	QTimer timer;
	BreakoutFrame frame;

	struct timeval last_step;

private slots:
	void step();
};