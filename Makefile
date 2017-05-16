ola: ola.c deque.c deque.h error.c error.h hashtable.c hashtable.h parser.c parser.h scanner.c scanner.h storage.c storage.h symboltable.c symboltable.h
	gcc -g -o ola ola.c deque.c error.c hashtable.c parser.c scanner.c storage.c symboltable.c

run: ola
	./ola test.ola

clean:
	rm -f ola *.h.gch
