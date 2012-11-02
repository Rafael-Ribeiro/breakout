#include "../Vector.hpp"

template <class T>
Vector<T>::Vector(size_t initial)
	: len(0), capacity(initial)
{
	this->data = new T[initial];
}

template <class T>
Vector<T>::Vector(const Vector<T>& o)
	: len(o.len), capacity(o.capacity)
{
	this->data = new T[o.capacity];
	for (size_t i = 0; i < o.len; i++)
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
const size_t& Vector<T>::length() const
{
	return this->len;
}

template <class T>
void Vector<T>::resize(const size_t& length)
{
	if (this->capacity < length)
	{
		delete [] this->data;
		this->data = new T[length];
		this->capacity = length;
	}

	this->len = length;
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

	for (size_t i = 0; i < o.len; i++)
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

	for (size_t i = 0; i < this->len; i++)
		if (this->data[i] != o.data[i])
			return false;

	return true;
}

template <class T>
T& Vector<T>::operator [](const size_t &x)
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
			for (size_t i = 0; i < this->len; i++)
				newdata[i] = std::move(this->data[i]);

			this->data = newdata;
		}

		this->len = x + 1;
	}

	return this->data[x];
}

template <class T>
const T& Vector<T>::operator [](const size_t &x) const
{
	return this->data[x];
}

template<class U>
std::ostream& operator << (std::ostream& c, const Vector<U>& v)
{
	if (v.len > 0)
	{
		c << v.data[0];

		for (size_t i = 1; i < v.len; i++)
			c << " " << v.data[i];

	}

	return c;
}