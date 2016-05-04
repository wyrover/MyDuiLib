task.o : Task.h Task.cpp
	g++ -c Task.cpp

test.o :
	g++ -c test.cpp

test: Task.o test.o
	g++ Task.o test.o -o test
clean:
	rm -f core *.o
