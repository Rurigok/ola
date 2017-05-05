all: ourlang.c scanner.c scanner.h
	gcc -o ourlang ourlang.c scanner.c
