options = -Wall -Wextra

bin = bin
src = src

run  : $(bin)\RBtree.exe
	$(bin)\RBtree.exe

test : $(bin)\RBtest.exe
	$(bin)\RBtest.exe

$(bin)\RBtest.exe : $(bin)\RBtree.o $(bin)\RBtest.o
	g++ $(bin)\RBtree.o $(bin)\RBtest.o -o $(bin)\RBtest.exe $(options)

$(bin)\RBtest.o : $(src)\RBtest.cpp $(src)\RBtree.h
	g++ -c $(src)\RBtest.cpp -o $(bin)\RBtest.o $(options)

$(bin)\RBtree.exe : $(bin)\RBtree.o $(src)\RBmain.cpp $(src)\RBtree.h
	g++ $(src)\RBmain.cpp $(bin)\RBtree.o -o $(bin)\RBtree.exe $(options)

$(bin)\RBtree.o : $(src)\RBtree.cpp $(src)\RBtree.h
	g++ -c $(src)\RBtree.cpp -o $(bin)\RBtree.o $(options)
