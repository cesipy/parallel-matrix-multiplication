all: src/matrix.c src/aux.c
	gcc src/matrix.c src/aux.c -o matrix

clean:
	rm -f src/a.out matrix