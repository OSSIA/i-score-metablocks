CC= gcc

CFLAGS= -std=c99 -g -Wall -Werror


OUTFILES= trad_ASM

all: $(OUTFILES)

trad_ASM: trad_ASM.o
	$(CC) $(CFLAGS) trad_ASM.o -o trad_ASM

trad_ASM.o: trad_ASM.c

clean :
	rm -f *.o $(OUTFILES)