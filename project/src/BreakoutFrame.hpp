#pragma once

#include <QFrame>

#include "Engine.hpp"

class BreakoutFrame
	: public QFrame
{
	Q_OBJECT

public:
	typedef QFrame super;
	BreakoutFrame(const Engine *engine, QWidget *parent = NULL);

private:
	const Engine* engine;
};