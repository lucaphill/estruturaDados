CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: PilhaChar.o main.o
	$(CC) $(CFLAGS) -o teste PilhaChar.o main.o

PilhaChar.o: PilhaChar.c PilhaChar.h
	$(CC) $(CFLAGS) -c PilhaChar.c

main.o: main.c PilhaChar.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste
