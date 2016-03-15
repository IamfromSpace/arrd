ZIP_DIR=arrd

arrd.zip: library.properties include/*.h
	mkdir ${ZIP_DIR}
	cp library.properties ${ZIP_DIR}/library.properties
	mkdir ${ZIP_DIR}/src
	cp include/arrd.h ${ZIP_DIR}/src/arrd.h
	cp include/arrd_internal.h ${ZIP_DIR}/src/arrd_internal.h
	zip -r -j arrd.zip ${ZIP_DIR}
	rm -rf ${ZIP_DIR}

.PHONY: clean
clean:
	rm -rf ${ZIP_DIR} || true
	rm *.o || true
	rm arrd.zip || true

.PHONY: test
test:
	g++ -g -pthread test/*.cpp -Iinclude/ -Itest/ -lgtest -o test.o && valgrind --leak-check=yes ./test.o

.PHONY: watch
watch:
	nodemon -e cpp,hpp,h test --exec "make test || exit 1"

.PHONY: perf
perf:
	g++ perf/*.cpp -L../hayai/src/ -I../hayai/src/ -Iinclude/ -lhayai_main -o perf.o && ./perf.o
