all: src/main.c src/matrix.c
	gcc src/matrix.c src/main.c -o matrix

# for testing, currently not in use
test: src/matrix.c src/test.c
	gcc src/matrix.c src/test.c -o test
clean:
	rm -f src/a.out matrix