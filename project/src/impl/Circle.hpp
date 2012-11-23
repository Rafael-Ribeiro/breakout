#include "../Circle.hpp"

double& Circle::radius()
{
	return this->_radius;
}

const double& Circle::radius() const
{
	return this->_radius;
}