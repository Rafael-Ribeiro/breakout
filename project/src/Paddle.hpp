class Paddle : MovingBody<Box>
{
	typedef MovingBody super;

	const double INITIAL_WIDTH = 50.0;
	const double INITIAL_HEIGHT = 10.0;
	const Box INITIAL_BOX(Paddle::INITIAL_WIDTH, Paddle::INITIAL_HEIGHT);

public:
	Paddle(const Point& initial_position, const Vector& initial_velocity)
	{
		Paddle::super(Paddle::INITIAL_BOX, Drawable<Box>(this), initial_position, initial_velocity);
	}
};