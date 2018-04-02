all: clean build

build: BayRandom.o CodeTree.o Bays4.o main.o
	g++ BayRandom.o CodeTree.o Bays4.o main.o -o main

BayRandom.o: ../yasc/BayRandom.cc ../yasc/BayRandom.h
	g++ -c -Wc++11-extensions ../yasc/BayRandom.cc

CodeTree.o:  ../yasc/CodeTree.cc  ../yasc/CodeTree.h
	g++ -c -Wc++11-extensions ../yasc/CodeTree.cc

Bays4.o: Bays4.cc Bays4.h
	g++ -c -Wc++11-extensions Bays4.cc

main.o:
	g++ -c -Wc++11-extensions main.cpp

clean:
	-rm main
	-rm *.o
