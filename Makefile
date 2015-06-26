CC= gcc

CFLAGS= -std=c99 -g -Wall -Werror


OUTFILES= function/main
OBJ= function/test_fun.o function/main.o function/trad_ASM.o 

all: $(OUTFILES)

function/main: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

function/main.o: function/main.c function/trad.h

function/trad_ASM.o: function/trad_ASM.c function/trad.h function/test_fun.h

function/test_fun.o: function/test_fun.c function/test_fun.h 

clean :
	rm -f function/*.o $(OUTFILES)