#pragma once

#include <QWidget>

#include "Engine.hpp"
#include "BreakoutFrame.hpp"

class BreakoutApp
	: public QWidget
{
	Q_OBJECT

public:
	typedef QWidget super;
	BreakoutApp(QWidget *parent = NULL);

private:
	Engine engine;
	BreakoutFrame frame;
};