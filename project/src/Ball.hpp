class Ball : MovingBody<Circle>
{
	typedef MovingBody super;
	const double BASE_RADIUS = 10.0;
	const Circle BASE_CIRCLE(Ball::RADIUS);

public:
	Ball(const Point& initial_position, const Vector& initial_velocity)
	{
		Ball::super(Circle::BASE_CIRCLE, DrawableCircle(this), initial_position, initial_velocity);
	}
};