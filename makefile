CC=gcc
MAIN=main.o
FLAGS= -Wall -g

all: stringProg

stringProg: $(MAIN)
	$(CC) $(FLAGS) -o stringProg $(MAIN) -lm

main.o: main.c 
	$(CC) $(FLAGS) -c main.c -lm


.PHONY: clean

clean:
	rm -f main.o stringProg