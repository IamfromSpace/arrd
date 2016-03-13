.PHONY: test
test:
	g++ -pthread test/*.cpp -Iinclude/ -Itest/ -lgtest -o test.o && ./test.o

.PHONY: watch
watch:
	nodemon -e cpp,hpp,h test --exec "make"

.PHONY: perf
perf:
	g++ perf/*.cpp -L../hayai/src/ -I../hayai/src/ -Iinclude/ -lhayai_main -o perf.o && ./perf.o
