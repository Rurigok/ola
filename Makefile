ola: ola.c scanner.c scanner.h error.c error.h list.c list.h parser.c parser.h
	gcc -g -o ola ola.c scanner.c error.c list.c parser.c

run: ola
	./ola test.ola

clean:
	rm -f ola *.h.gch
