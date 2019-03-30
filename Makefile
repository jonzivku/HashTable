# makefile for p5, for a hash table

# defining target dependencies and files
p5: main.o HashTable.o
	g++ -o p5 main.o HashTable.o -Wall

# defining how each object file is to be built
main.o: main.cpp HashTable.h
	g++ -c main.cpp -Wall

HashTable.o: HashTable.cpp HashTable.h
	g++ -c HashTable.cpp -Wall

# clean up
clean:
	rm -f p5 *.o *~
