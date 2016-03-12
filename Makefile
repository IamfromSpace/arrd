.PHONY: test
test:
	g++ -pthread test/*.cpp -Isrc/ -Itest/ -lgtest -o test.o && ./test.o

.PHONY: perf
perf:
	g++ perf/*.cpp -L../hayai/src/ -I../hayai/src/ -Isrc/ -lhayai_main -o perf.o && ./perf.o
