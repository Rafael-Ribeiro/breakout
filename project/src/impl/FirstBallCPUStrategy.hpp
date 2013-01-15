#include "../FirstBallCPUStrategy.hpp"

FirstBallCPUStrategy::FirstBallCPUStrategy()
{
}

void FirstBallCPUStrategy::step(Player &player, const BreakoutWorld &world, const double &dt) const
{
	set<Ball*>::iterator it = world.balls().begin();
	set<Ball*>::iterator end = world.balls().end();

	double best_toc = numeric_limits<double>::infinity();

	bool left = false;
	bool right = false;
	bool stop = true;
	for (; it != end; it++)
	{
		double& p_y = player.paddle()->position().y();
		double b_vy = p_y - (*it)->velocity().y();

		if (b_vy < numeric_limits<double>::epsilon())
			continue;

		double dy = fabs(p_y - (*it)->position().y());

		double toc = dy / b_vy;

		if (toc < best_toc)
		{
			best_toc = toc;
			left = (*it)->position().x() - player.paddle()->left() < numeric_limits<double>::epsilon();
			right = (*it)->position().x() - player.paddle()->right() > numeric_limits<double>::epsilon();
			stop = fabs((*it)->position().x() - player.paddle()->position().x()) < 8;
		}
	}

	if (left)
		player.left();

	else if (right)
		player.right();

	else if (stop)
		player.stop();

}