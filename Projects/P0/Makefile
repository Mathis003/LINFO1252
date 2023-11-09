CC=gcc
FLAGS=-Wall -g
OUTPUT=main.out

run: compile
	./main.out

compile: memory_management.c
	${CC} ${FLAGS} -o ${OUTPUT} memory_management.c

clean:
	rm -f ${OUTPUT}