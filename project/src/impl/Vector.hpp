#include <cmath>
#include <limits>

#include "../Vector.hpp"

using namespace std;

Vector& Vector::operator = (const Vector& other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

bool Vector::operator == (const Vector& other) const
{
	return fabs(this->x - other.x) < numeric_limits<double>::epsilon() && fabs(this->y - other.y) < numeric_limits<double>::epsilon();
}

Vector Vector::operator + (const Vector& other) const
{
	return Vector(this->x + other.x, this->y + other.y);
}

Vector Vector::operator - (const Vector& other) const
{
	return Vector(this->x - other.x, this->y - other.y);
}

double Vector::operator * (const Vector& other) const
{
	return this->x * other.x + this->y * other.y;
}

Vector Vector::operator * (const double& ratio) const
{
	return Vector(this->x * ratio, this->y * ratio);
}

Vector Vector::operator / (const double& ratio) const
{
	return Vector(this->x / ratio, this->y / ratio);
}

Vector& Vector::operator += (const Vector& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector& Vector::operator -= (const Vector& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector& Vector::operator *= (const double& ratio)
{
	this->x *= ratio;
	this->y *= ratio;
	return *this;
}

Vector& Vector::operator /= (const double& ratio)
{
	this->x /= ratio;
	this->y /= ratio;
	return *this;
}

Vector Vector::operator - () const
{
	return Vector(-this->x, -this->y);	
}

Vector Vector::normal() const
{
	return Vector(-this->y, this->x);
}

Vector Vector::reflect(const Vector& incident) const
{
	return *this * (incident * *this * 2) - incident;
}

Vector& Vector::normalize()
{
	double length = this->length();

	if (fabs(length) > numeric_limits<double>::epsilon()) /* length != 0 */
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
	return out << "(" << v.x << ", " << v.y << ")";
}
