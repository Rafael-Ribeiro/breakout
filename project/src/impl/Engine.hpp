#include "../Engine.hpp"

Engine::Engine()
	: _bodies(), _movables()
{
	this->_bodies.insert(new Ball(Point(400, 400), Vector(1, 0)));
}

Engine::~Engine()
{
	set<Body*>::iterator it = this->_bodies.begin();
	set<Body*>::iterator end = this->_bodies.end();
	
	for (; it != end; it++)
		delete *it;
}

const set<Body*>& Engine::bodies() const
{
	return this->_bodies;
}