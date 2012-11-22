template <class S>
class Drawable
{
	Body<S>* body;

public:
	Drawable(Body<S>* body)
		: body(body)
	{
	}

	void draw(BreakoutFrame& frame) const;
};

template<>
Drawable<Box>::draw(BreakoutFrame& frame) const
{

}

template<>
Drawable<Circle>::draw(BreakoutFrame& frame) const
{

}