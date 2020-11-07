options = -Wall -Wextra

run : RBtree.exe
	RBtree.exe

RBtree.exe : RBtree.cpp RBtree.h RBmain.cpp 
	g++ RBmain.cpp RBtree.cpp -o RBtree.exe $(options)