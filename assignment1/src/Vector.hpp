#pragma once

#include <iostream>
#include <utility>

template<class T>
class Vector
{
	template<class U>
	friend std::ostream& operator<<(std::ostream&, const Vector<U>&);

protected:
	T* data;
	unsigned int len;
	unsigned int capacity;

public:
	Vector(unsigned int = 10);

	Vector(const Vector<T>&);
	Vector(Vector<T>&&);

	virtual ~Vector();

	unsigned int length() const;

	Vector<T>& operator =(const Vector<T>&);
	Vector<T>& operator =(Vector<T>&&);

	bool operator ==(const Vector<T>&) const;

	T& operator [](unsigned int);
	const T& operator [](unsigned int) const;
};

/* implementation */

template <class T>
Vector<T>::Vector(unsigned int initial)
	: len(0), capacity(initial)
{
	this->data = new T[initial];
}

template <class T>
Vector<T>::Vector(const Vector<T>& o)
	: len(o.len), capacity(o.capacity)
{
	this->data = new T[o.capacity];
	for (unsigned int i = 0; i < o.len; i++)
		this->data[i] = o.data[i];
}

template <class T>
Vector<T>::Vector(Vector<T>&& o)
{
	*this = std::forward< Vector<T> >(o);
}

template <class T>
Vector<T>::~Vector()
{
	delete [] this->data;
}

template <class T>
unsigned int Vector<T>::length() const
{
	return this->len;
}

template <class T>
Vector<T>& Vector<T>::operator = (const Vector<T>& o)
{	
	if (this == &o)
		return *this;

	this->len = o.len;

	if (this->capacity < o.len)
	{
		delete [] this->data;

		this->data = new T[o.capacity];
		this->capacity = o.capacity;
	}

	for (unsigned int i = 0; i < o.len; i++)
		this->data[i] = o.data[i];

	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator =(Vector<T>&& o)
{
	this->len = o.len;
	this->capacity = o.capacity;
	this->data = o.data;

	o.data = NULL;

	return *this;
}

template <class T>
bool Vector<T>::operator ==(const Vector<T>& o) const
{
	if (this == &o)
		return true;

	if (this->len != o.len)
		return false;

	for (unsigned int i = 0; i < this->len; i++)
		if (this->data[i] != o.data[i])
			return false;

	return true;
}

template <class T>
T& Vector<T>::operator [](unsigned int x)
{
	if (x >= this->len)
	{
		if (x >= this->capacity)
		{
			do
			{
				this->capacity *= 2;

			} while (x >= this->capacity);

			T* newdata = new T[this->capacity];
			for (unsigned int i = 0; i < this->len; i++)
				newdata[i] = std::move(this->data[i]);

			this->data = newdata;
		}

		this->len = x + 1;
	}

	return this->data[x];
}

template <class T>
const T& Vector<T>::operator [](unsigned int x) const
{
	return this->data[x];
}

template<class U>
std::ostream& operator << (std::ostream& c, const Vector<U>& v)
{
	if (v.len > 0)
	{
		c << v.data[0];

		for (unsigned int i = 1; i < v.len; i++)
			c << " " << v.data[i];

	}

	return c;
}
