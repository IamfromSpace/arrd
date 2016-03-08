test:
	g++ -pthread *.h *.cpp -lgtest -o test.o && ./test.o
