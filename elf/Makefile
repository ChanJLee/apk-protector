all: clean build

build: main.o
	g++ main.o -o main

main.o:
	g++ -c -std=c++11 main.cpp

clean:
	-rm main
	-rm *.o
