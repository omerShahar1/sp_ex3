CC=gcc
MAIN=main.o
FLAGS= -Wall -g

# note that in the makefile i called the final runing program "stringProg" as you requested in the instructins.
# however, in the cheking program you created, "check_submition.py", you called the final program by the name "connections".
# therefore the cheking program you created will only work if you change the name from "connections" to the correct name
# you requested: "stringProg". 

all: stringProg

stringProg: $(MAIN)
	$(CC) $(FLAGS) -o stringProg $(MAIN) -lm

main.o: main.c 
	$(CC) $(FLAGS) -c main.c -lm


.PHONY: clean

clean:
	rm -f main.o stringProg