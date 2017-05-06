ola: ola.c scanner.c scanner.h
	gcc -g -o ola ola.c scanner.c

run: ola
	./ola test.ola

clean:
	rm -f ola *.h.gch
