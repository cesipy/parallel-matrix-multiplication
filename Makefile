all: src/matrix.c
	gcc src/matrix.c -o matrix

clean:
	rm -f src/a.out matrix