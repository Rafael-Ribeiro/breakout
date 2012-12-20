#pragma once

#include <iostream>

using namespace std;

class Vector
{
	double _x;
	double _y;

	friend ostream& operator << (ostream &out, const Vector &v);

public:
	Vector(const double &x = 0.0, const double &y = 0.0)
		: _x(x), _y(y)
	{
	}

	double& x();
	const double& x() const;

	double& y();
	const double& y() const;
	
	Vector& operator = (const Vector &other);
	bool operator == (const Vector &other) const;

	Vector operator + (const Vector &other) const;
	Vector operator - (const Vector &other) const;
	double operator * (const Vector &other) const;
	Vector operator * (const double &ratio) const;
	Vector operator / (const double &ratio) const;

	Vector& operator += (const Vector &other);
	Vector& operator -= (const Vector &other);
	Vector& operator *= (const double &ratio);
	Vector& operator /= (const double &ratio);

	Vector operator -() const;

	Vector normal() const;
	Vector reflect(const Vector &incident) const;

	Vector& normalize();
	double length() const;
	double sqrd_length() const;
};