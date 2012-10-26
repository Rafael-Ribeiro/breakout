#pragma once

#include <utility>

#include "Vector.hpp"

template <class K, class V>
class AssociativeArrayC
{
	typedef Vector<std::pair<K,V> > Container;
	Container data;

	template<class Q, class W>
	friend std::ostream& operator<<(std::ostream&, const AssociativeArrayC<Q,W>&);

public:
	AssociativeArrayC(unsigned int = 10);

	AssociativeArrayC(const AssociativeArrayC<K,V>&);
	AssociativeArrayC(AssociativeArrayC<K,V>&&);

	AssociativeArrayC<K,V>& operator =(const AssociativeArrayC<K,V>&);
	AssociativeArrayC<K,V>& operator =(AssociativeArrayC<K,V>&&);

	bool operator ==(const AssociativeArrayC<K,V>&) const;

	V& operator [](const K&);
};

/* implementation */
template <class K, class V>
AssociativeArrayC<K,V>::AssociativeArrayC(unsigned int initial)
	: data(initial)
{
}

template <class K, class V>
AssociativeArrayC<K,V>::AssociativeArrayC(const AssociativeArrayC<K,V>& o)
	: data(o.data)
{
}

template <class K, class V>
AssociativeArrayC<K,V>::AssociativeArrayC(AssociativeArrayC<K,V>&& o)
	: data(std::forward<Container>(o.data))
{
}

template <class K, class V>
AssociativeArrayC<K,V>& AssociativeArrayC<K,V>::operator =(const AssociativeArrayC<K,V>& o)
{
	this->data = o.data;
	return *this;
}

template <class K, class V>
AssociativeArrayC<K,V>& AssociativeArrayC<K,V>::operator =(AssociativeArrayC<K,V>&& o)
{
	this->data = std::move(o.data);
	return *this;
}

template <class K, class V>
V& AssociativeArrayC<K,V>::operator [](const K& key)
{
	for (unsigned int i = 0; i < this->data.length(); i++)
		if (this->data[i].first == key)
			return this->data[i].second;

	std::pair<K,V>& a = this->data[this->data.length()];
	a.first = key;

	return a.second;
}

/* used in ofstream << assoc; */
template<class Q, class W>
std::ostream& operator << (std::ostream& c, const AssociativeArrayC<Q,W>& a)
{
	return c << a.data;
}

template <class K, class V>
bool AssociativeArrayC<K,V>::operator ==(const AssociativeArrayC<K,V>& o) const
{
	if (this->data.length() != o.data.length())
		return false;

	for (unsigned int i = 0; i < this->data.length(); i++)
	{
		unsigned int j;
		for (j = 0; j < this->data.length(); j++)
			if (this->data[i] == o.data[j])
				break;

		if (j == this->data.length())
			return false;
	}

	return true;
}
