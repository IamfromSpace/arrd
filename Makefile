.PHONY: test
test:
	g++ -pthread src/*.h test/*.cpp -Isrc/ -lgtest -o test.o && ./test.o
