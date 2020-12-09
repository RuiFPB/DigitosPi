# modificar o CXX/CXXw para o compilador desejado
CXXw = x86_64-w64-mingw32-g++
CXX = g++

default: 
	@echo "Utilização: make [os]"
	@echo "	os: linux ou win32"
	@echo "		linux compila o programa para sistemas linux utilizando g++"
	@echo "		win32 compila o programa para sistemas windows utilizando mingw32 (O programa deve ser compilado através de um sistema linux. Uma instalação de mingw32 no windows não irá funcionar sem alterações ao Makefile)"

linux: pi2
pi2 : pi2.o
	$(CXX) -O -o pi2 pi2.o -static-libgcc -static-libstdc++
pi2.o : pi2.cpp pi2.h
	$(CXX) -c pi2.cpp

win: pi2w
pi2w: pi2w.o
	$(CXXw) -O -o pi2 pi2w.o -static-libgcc -static-libstdc++
pi2w.o: pi2.cpp pi2.h
	$(CXXw) -c pi2.cpp -o pi2w.o
