all: clean build

build: BayRandom.o CodeTree.o Bays4.o main.o
	g++ BayRandom.o CodeTree.o Bays4.o main.o -o main

BayRandom.o: ../../lib/src/main/cpp/BayRandom.cc ../../lib/src/main/cpp/BayRandom.h
	g++ -c ../../lib/src/main/cpp/BayRandom.cc

CodeTree.o:  ../../lib/src/main/cpp/CodeTree.cc  ../../lib/src/main/cpp/CodeTree.h
	g++ -c ../../lib/src/main/cpp/CodeTree.cc

Bays4.o: ../../lib/src/main/cpp/Bays4.cc ../../lib/src/main/cpp/Bays4.h
	g++ -c ../../lib/src/main/cpp/Bays4.cc

main.o:
	g++ -c main.cpp

clean:
	rm *.o
