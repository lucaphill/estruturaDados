CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: pilhaDupla.o main.o
	$(CC) $(CFLAGS) -o teste pilhaDupla.o main.o

pilhaDupla.o: pilhaDupla.c pilhaDupla.h
	$(CC) $(CFLAGS) -c pilhaDupla.c

main.o: main.c pilhaDupla.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste
