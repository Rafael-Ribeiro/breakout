#include <QKeyEvent>

#include "Paddle.hpp"

class CPUPlayer : public Player
{
	typedef Player super;

	Qt::Key left_key;
	Qt::Key right_key;

public:
	CPUPlayer(Paddle *paddle);

	void step(const double &dt);
};