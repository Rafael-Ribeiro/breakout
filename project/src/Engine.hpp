#include <set>

using namespace std;

class Engine
{
	set<Body> static_bodies;
	set<MovingBody> moving_bodies;

public:
	void step(const double& dt);
};