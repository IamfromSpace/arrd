.PHONY: test
test:
	g++ -pthread src/*.h test/*.cpp -Isrc/ -lgtest -o test.o && ./test.o

.PHONY: perf
perf:
	g++ perf/*.cpp -L../hayai/src/ -I../hayai/src/ -Isrc/ -lhayai_main -o perf.o && ./perf.o
