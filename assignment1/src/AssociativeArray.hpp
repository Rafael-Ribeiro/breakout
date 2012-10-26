#include "AssociativeArrayI.hpp"
#include "AssociativeArrayC.hpp"

template <class K, class V>
using AssociativeArray = AssociativeArrayI<K,V>;

/* common */
template<class K, class V>
std::ostream& operator << (std::ostream& c, const std::pair<K,V>& p)
{
	return c << "(" << p.first << ", " << p.second << ")";
}
