.PHONY: test
test:
	g++ -g -pthread test/*.cpp -Iinclude/ -Itest/ -lgtest -o test.o && valgrind --leak-check=yes ./test.o

.PHONY: watch
watch:
	nodemon -e cpp,hpp,h test --exec "make test || exit 1"

.PHONY: perf
perf:
	g++ perf/*.cpp -L../hayai/src/ -I../hayai/src/ -Iinclude/ -lhayai_main -o perf.o && ./perf.o
