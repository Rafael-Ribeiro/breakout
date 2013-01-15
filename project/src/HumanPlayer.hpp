#pragma once

#include <QKeyEvent>

#include "Paddle.hpp"

class HumanPlayer : public Player
{
	typedef Player super;

	Qt::Key left_key;
	Qt::Key right_key;

public:
	HumanPlayer(Paddle *paddle, Qt::Key left_key = Qt::Key::Key_Left, Qt::Key right_key = Qt::Key::Key_Right);

	void step(const BreakoutWorld &world, const double &dt);
};