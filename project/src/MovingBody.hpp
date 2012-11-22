template <class S>
class MovingBody : public Body<S>
{
	typedef Body super; 
	Vector velocity;

protected:
	MovingBody(const S& shape, const Drawable& drawable, const Vector& initial_position, const Vector& initial_velocity)
		: super(shape, drawable, initial_position), initial_velocity(velocity)
	{
	}

public:
	void step();
};