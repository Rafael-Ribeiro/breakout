class Shape
{
	virtual Contact collides(const Shape& other, const Point& this_position, const Point& other_position);
};