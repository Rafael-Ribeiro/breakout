#include "../ClosestBallCPUStrategy.hpp"

ClosestBallCPUStrategy::ClosestBallCPUStrategy()
{
}

void ClosestBallCPUStrategy::step(Player &player, const BreakoutWorld &world, const double &dt) const
{
	set<Ball*>::iterator it = world.balls().begin();
	set<Ball*>::iterator end = world.balls().end();

	double min_dist = numeric_limits<double>::infinity();

	bool left = false;
	bool right = false;
	bool stop = true;
	for (; it != end; it++)
	{
		double& y = player.paddle()->position().y();

		Vector dp1 = Vector(player.paddle()->left(), y) - (*it)->position();
		Vector dp2 = Vector(player.paddle()->right(), y) - (*it)->position();
		Vector dpc = Vector(player.paddle()->position().x(), y) - (*it)->position();

		double dist1 = dp1.sqrd_length();
		double dist2 = dp2.sqrd_length();

		Vector& dp = dist1 < dist2 ? dp1 : dp2;
		double& dist = dist1 < dist2 ? dist1 : dist2;

		if (dist < min_dist)
		{
			min_dist = dist;
			left = (*it)->position().x() < player.paddle()->left();
			right = (*it)->position().x() > player.paddle()->right();
			stop = fabs(dpc.x()) < 8;
		}
	}

	if (left)
		player.left();

	else if (right)
		player.right();

	else if (stop)
		player.stop();

}