#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <utility>

template<class T>
class Vector
{
	template<class U>
	friend std::ostream& operator<<(std::ostream&, const Vector<U>&);

protected:
	T* data;
	size_t len;
	size_t capacity;

public:
	Vector(size_t initial = 10);

	Vector(const Vector<T>&);
	Vector(Vector<T>&&);

	virtual ~Vector();

	const size_t& length() const;
	void resize(const size_t& length);

	Vector<T>& operator =(const Vector<T>& o);
	Vector<T>& operator =(Vector<T>&& o);

	bool operator ==(const Vector<T>& o) const;

	T& operator [](const size_t &x);
	const T& operator [](const size_t &x) const;
};

#endif
