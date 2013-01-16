#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTimer>

#include <sys/time.h>

#include "BreakoutWorld.hpp"
#include "BreakoutFrame.hpp"

namespace breakout
{

namespace gui
{

class BreakoutWindow
	: public QMainWindow
{
	Q_OBJECT

public:
	typedef QMainWindow super;
	BreakoutWindow(string level_filename_path, Player *player_1, Player *player_2, QWidget *parent = NULL);

private:
	BreakoutWorld world;
	QTimer timer;
	BreakoutFrame frame;

	struct timeval last_step;

private slots:
	void step();
};

}
}