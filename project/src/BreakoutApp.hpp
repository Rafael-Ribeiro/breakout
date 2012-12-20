#pragma once

#include <QWidget>
#include <QVBoxLayout>

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
	QVBoxLayout layout;
	BreakoutFrame frame;
};