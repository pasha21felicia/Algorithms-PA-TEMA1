CC = g++
CFLAGS = -Wall -g

build: 
	g++ -Wall -g -o crypto crypto.cpp
	g++ -Wall -g -o valley valley.cpp
	g++ -Wall -g -o ridge ridge.cpp
	g++ -Wall -g -o stocks stocks.cpp

run-p1:
	./crypto

run-p2:
	./stocks

run-p3:
	./valley

run-p4:
	./ridge
clean: 
	rm -f crypto valley ridge stocks