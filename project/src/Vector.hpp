class Vector
{
public:
	static double EPS = 1e-14;

private:
	double x;
	double y;

public:
	Vector(const double& x = 0.0, const double& y = 0.0)
		: x(x), y(y)
	{
	}

	Vector operator = (const Vector& other);
	Vector operator += (const Vector& other);
	Vector operator -= (const Vector& other);
	
	bool operator == (const Vector& other) const;
	Vector operator + (const Vector& other) const;
	Vector operator - (const Vector& other) const;
	Vector operator * (const double& ratio) const;
	Vector operator / (const double& ratio) const;

	Vector operator -() const;

	Vector normal() const;
	Vector reflect(const Vector& incident) const;

	Vector& normalize();
	const double& length() const;
};