all: src/matrix.c src/aux.c
	gcc src/matrix.c src/aux.c -o matrix


test: src/aux.c src/test.c
	gcc src/aux.c src/test.c -o test
clean:
	rm -f src/a.out matrix