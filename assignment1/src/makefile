CC = g++-4.7 -std=c++11 -g
 
all: main.o
	${CC} main.o -o main

clean:
	rm -f *.o *~ main

main.o: main.cpp Vector.hpp AssociativeArrayI.hpp AssociativeArrayC.hpp
	${CC} main.cpp -c -o main.o

