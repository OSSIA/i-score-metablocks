CC= gcc

CFLAGS= -std=c99 -g -Wall -Werror


OUTFILES= main
OBJ= test_fun.o main.o trad_ASM.o 

all: $(OUTFILES)

main: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

main.o: main.c trad.h

trad_ASM.o: trad_ASM.c trad.h test_fun.h

test_fun.o: test_fun.c test_fun.h 

clean :
	rm -f *.o $(OUTFILES)