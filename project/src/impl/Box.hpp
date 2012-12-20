#include "../Box.hpp"

double& Box::width()
{
	return this->_width;
}

const double& Box::width() const
{
	return this->_width;
}

double& Box::height()
{
	return this->_height;
}

const double& Box::height() const
{
	return this->_height;
}