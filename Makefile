CXX = g++

pi2 : pi2.o
	$(CXX) -O -o pi2 pi2.o
pi2.o : pi2.cpp pi2.h
	$(CXX) -c pi2.h pi2.cpp