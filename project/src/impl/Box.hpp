#include "../Box.hpp"

double& Box::hwidth()
{
	return this->_hwidth;
}

const double& Box::hwidth() const
{
	return this->_hwidth;
}

double& Box::hheight()
{
	return this->_hheight;
}

const double& Box::hheight() const
{
	return this->_hheight;
}

double Box::width() const
{
	return this->_hwidth * 2;
}

double Box::height() const
{
	return this->_hheight * 2;
}

double Box::top() const
{
	return this->position().y() + this->hheight();
}

double Box::bottom() const
{
	return this->position().y() - this->hheight();	
}

double Box::left() const
{
	return this->position().x() - this->hwidth();	
}

double Box::right() const
{
	return this->position().x() + this->hwidth();	
}
