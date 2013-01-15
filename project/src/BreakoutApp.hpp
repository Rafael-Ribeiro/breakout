#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTimer>

#include <sys/time.h>

#include "BreakoutWorld.hpp"
#include "BreakoutFrame.hpp"

class BreakoutApp
	: public QMainWindow
{
	Q_OBJECT

public:
	typedef QMainWindow super;
	BreakoutApp(QWidget *parent = NULL);

private:
	BreakoutWorld world;
	QTimer timer;
	BreakoutFrame frame;

	struct timeval last_step;

private slots:
	void step();
};