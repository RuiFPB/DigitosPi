CXX = x86_64-w64-mingw32-g++

pi2 : pi2.o
	$(CXX) -O -o pi2 pi2.o -static-libgcc -static-libstdc++
pi2.o : pi2.cpp pi2.h
	$(CXX) -c pi2.h pi2.cpp