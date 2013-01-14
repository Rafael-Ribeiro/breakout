#include <cmath>
#include <limits>

#include "../Vector.hpp"

using namespace std;

double& Vector::x()
{
	return this->_x;
}

const double& Vector::x() const
{
	return this->_x;
}

double& Vector::y()
{
	return this->_y;
}

const double& Vector::y() const
{
	return this->_y;
}

Vector& Vector::operator = (const Vector& other)
{
	this->_x = other._x;
	this->_y = other._y;
	return *this;
}

bool Vector::operator == (const Vector& other) const
{
	return fabs(this->_x - other._x) < numeric_limits<double>::epsilon() && fabs(this->_y - other._y) < numeric_limits<double>::epsilon();
}

bool Vector::operator != (const Vector& other) const
{
	return fabs(this->_x - other._x) > numeric_limits<double>::epsilon() || fabs(this->_y - other._y) > numeric_limits<double>::epsilon();
}

Vector Vector::operator + (const Vector& other) const
{
	return Vector(this->_x + other._x, this->_y + other._y);
}

Vector Vector::operator - (const Vector& other) const
{
	return Vector(this->_x - other._x, this->_y - other._y);
}

double Vector::operator * (const Vector& other) const
{
	return this->_x * other._x + this->_y * other._y;
}

Vector Vector::operator * (const double& ratio) const
{
	return Vector(this->_x * ratio, this->_y * ratio);
}

Vector Vector::operator / (const double& ratio) const
{
	return Vector(this->_x / ratio, this->_y / ratio);
}

Vector& Vector::operator += (const Vector& other)
{
	this->_x += other._x;
	this->_y += other._y;
	return *this;
}

Vector& Vector::operator -= (const Vector& other)
{
	this->_x -= other._x;
	this->_y -= other._y;
	return *this;
}

Vector& Vector::operator *= (const double& ratio)
{
	this->_x *= ratio;
	this->_y *= ratio;
	return *this;
}

Vector& Vector::operator /= (const double& ratio)
{
	this->_x /= ratio;
	this->_y /= ratio;
	return *this;
}

Vector Vector::operator - () const
{
	return Vector(-this->_x, -this->_y);	
}

Vector Vector::normal() const
{
	return Vector(-this->_y, this->_x);
}

Vector Vector::reflect(const Vector& incident) const
{
	return - (*this * (incident * *this * 2) - incident);
}

Vector& Vector::normalize()
{
	double length = this->length();

	if (length > numeric_limits<double>::epsilon()) /* length != 0 */
		*this /= length;

	return *this;
}

double Vector::length() const
{
	return sqrt(this->sqrd_length());
}

double Vector::sqrd_length() const
{
	return *this * *this;
}

ostream& operator << (ostream &out, const Vector &v)
{
	return out << "(" << v.x() << ", " << v.y() << ")";
}
