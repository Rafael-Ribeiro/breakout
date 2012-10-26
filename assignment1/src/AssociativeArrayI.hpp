#pragma once

#include <utility>

#include "Vector.hpp"

template <class K, class V>
class AssociativeArrayI : public Vector<std::pair<K,V> >
{
	typedef Vector<std::pair<K,V> > super;

public:
	AssociativeArrayI(unsigned int = 10);

	AssociativeArrayI(const AssociativeArrayI<K,V>&);
	AssociativeArrayI(AssociativeArrayI<K,V>&&);

	AssociativeArrayI<K,V>& operator =(const AssociativeArrayI<K,V>&);
	AssociativeArrayI<K,V>& operator =(AssociativeArrayI<K,V>&&);

	bool operator ==(const AssociativeArrayI<K,V>&) const;

	V& operator [](const K&);
};

/* implementation */
template <class K, class V>
AssociativeArrayI<K,V>::AssociativeArrayI(unsigned int initial)
	: super(initial)
{
}

template <class K, class V>
AssociativeArrayI<K,V>::AssociativeArrayI(const AssociativeArrayI<K,V>& o)
	: super(o)
{
}

template <class K, class V>
AssociativeArrayI<K,V>::AssociativeArrayI(AssociativeArrayI<K,V>&& o)
	: super(std::forward<super>(o))
{
}

template <class K, class V>
AssociativeArrayI<K,V>& AssociativeArrayI<K,V>::operator =(const AssociativeArrayI<K,V>& o)
{
	super::operator=(o);
	return *this;
}

template <class K, class V>
AssociativeArrayI<K,V>& AssociativeArrayI<K,V>::operator =(AssociativeArrayI<K,V>&& o)
{
	return super::operator=(std::forward<super>(o));
}

template <class K, class V>
V& AssociativeArrayI<K,V>::operator [](const K& key)
{
	for (unsigned int i = 0; i < this->len; i++)
		if (this->data[i].first == key)
			return this->data[i].second;

	std::pair<K,V>& a = super::operator[](this->len);
	a.first = key;

	return a.second;
}

template <class K, class V>
bool AssociativeArrayI<K,V>::operator ==(const AssociativeArrayI<K,V>& o) const
{
	if (this->len != o.len)
		return false;

	for (unsigned int i = 0; i < this->len; i++)
	{
		unsigned int j;
		for (j = 0; j < this->len; j++)
			if (this->data[i] == o.data[j])
				break;

		if (j == this->len)
			return false;
	}

	return true;
}

