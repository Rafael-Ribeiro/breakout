#include "../Movable.hpp"

Vector& Movable::velocity()
{
	return this->_velocity;
}

const Vector& Movable::velocity() const
{
	return this->_velocity;
}

void Movable::step(const double &dt)
{
	this->_position += this->_velocity * dt;
}