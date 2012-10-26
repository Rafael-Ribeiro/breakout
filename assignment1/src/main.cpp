#include <iostream>
#include <cassert>
#include <string>

#include "Vector.hpp"
#include "AssociativeArray.hpp"

void testAssociativeArray()
{
	AssociativeArray<std::string, int> table;
	table["abc"] = 15;
	table["jkl"] = 12;
	table["xyz"] = 85;

	assert(table["jkl"] == 12);

	AssociativeArray<int, int> table2;
	table2[-1] = -1;
	assert(table2[-1] == -1);

	AssociativeArray<int,std::string> A(10);
	AssociativeArray<int,std::string> B(A);

	assert(A == B);

	AssociativeArray<int, std::string> C;
	C[0] == "A";
	C[1] == "B";

	AssociativeArray<int, std::string> D;
	D[1] == "B";
	D[0] == "A";

	assert(C == D);
}

void testVector()
{
	Vector<int> v(1);

	for (int i = 0; i < 10; i++)
		v[i] = i*10;

	Vector<int> c(v);
	assert(v == c);

	Vector<int> d = std::move(v);
	assert(d == c);
}

int main()
{
	testVector();
	testAssociativeArray();

	return 0;
}
