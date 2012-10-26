#include <iostream>
#include <cassert>
#include <string>

#include "Vector.hpp"
#include "AssociativeArray.hpp"

#define DEBUG

void testVector()
{
	Vector<int> vect = Vector<int>(10);
	Vector<int> vect2 = Vector<int>(10);

	for (unsigned int i = 0; i < 10; i++)
		vect[i] = vect2[i] = i;

	vect[6] = vect2[6] = -1;

	assert(vect[5] == 5 && vect2[5] == 5);
	assert(vect[6] == -1 && vect2[6] == -1);
	assert(vect[7] == 7 && vect2[7] == 7);

	vect[10] = vect2[10] = 10;

	assert(vect[5] == 5 && vect2[5] == 5);
	assert(vect[6] == -1 && vect2[6] == -1);
	assert(vect[10] == 10 && vect2[10] == 10);

	assert(vect == vect2);
	#ifdef DEBUG
		std::cout << "assert(vect == vect2) successful" << std::endl;
		std::cout << vect << std::endl;
		std::cout << vect2 << std::endl;
	#endif

	vect[6] = 0;

	assert(!(vect == vect2));
	#ifdef DEBUG
		std::cout << std::endl << "assert(!(vect == vect2)) successful (after vect[6] = 0)" << std::endl;
		std::cout << vect << std::endl;
		std::cout << vect2 << std::endl;
	#endif

	vect = vect2;
	assert(vect == vect2); // they're equal (not the same) again

	Vector<int> vect3 = std::move(vect2);
	assert(vect3 == vect);
}

void testAssociativeArray()
{
	AssociativeArray<std::string, int> table;
	AssociativeArray<std::string, int> table2;

	table["abc"] = table2["abc"] = 15;
	table["jkl"] = table2["jkl"] = 12;
	table["xyz"] = table2["xyz"] = 85;

	assert(table["jkl"] == 12);

	table["a"] = table2["a"] = 1;
	table["b"] = table2["b"] = 2;
	table["c"] = table2["c"] = 3;
	table["d"] = table2["d"] = 4;
	table["e"] = table2["e"] = 5;
	table["f"] = table2["f"] = 6;
	table["g"] = table2["g"] = 7;
	table["h"] = table2["h"] = 8; // the 11th element expands the assoc_arr

	// Assigning in different order
	table["i"] = 9;
	table["j"] = 10;
	table2["j"] = 10;
	table2["i"] = 9;

	assert(table == table2);
	#ifdef DEBUG
		std::cout << "assert(table == table2) successful (order doesn't count):" << std::endl;
		std::cout << table << std::endl;
		std::cout << table2 << std::endl;
	#endif

	table["i"] = 0;
	assert(!(table == table2));
	#ifdef DEBUG
		std::cout << std::endl << "assert(!(table == table2)) successful (after table[\"i\"] = 0):" << std::endl;
		std::cout << table << std::endl;
		std::cout << table2 << std::endl;
	#endif

	table2["i"] = 0;
	assert(table == table2);
	#ifdef DEBUG
		std::cout << std::endl << "assert(table == table2) successful (after table2[\"i\"] = 0):" << std::endl;
		std::cout << table << std::endl;
		std::cout << table2 << std::endl;
	#endif

	table["i"] = 1; // they're different again! but:
	table = table2;
	assert(table == table2);

	AssociativeArray<int, int> table3;
	table3[-1] = -1;
	assert(table3[-1] == -1);


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

int main()
{
	testVector();
	std::cout << std::endl;

	testAssociativeArray();

	return 0;
}
