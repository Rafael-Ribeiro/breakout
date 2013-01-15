#include "Point.hpp"

struct BodyMemento 
{
	Point position;
	BodyMemento(const Point& position) : position(position) { }
};