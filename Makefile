CC=gcc
CFLAGS=  -Wall -Wextra -c -ggdb  -std=c99 -O0
LFLAGS=  -Wall -Wextra  -std=c99 -ggdb


integer.o:
	$(CC) $(CFLAGS) integer.c integer.h
dll.o:
	$(CC) $(CFLAGS) dll.c dll.h
binomial.o:
	$(CC) $(CFLAGS) binomial.c binomial.h


dlltest: integer.o  dll.o
	$(CC) $(CFLAGS) dll-0-0.c
	$(CC) $(CFLAGS) dll-4-10.c
	$(CC) $(LFLAGS) integer.o dll.o dll-0-0.o -o dlltest0
	$(CC) $(LFLAGS) integer.o dll.o dll-4-10.o -o dlltest1
binomialtest: binomial.o dll.o integer.o
	$(CC) $(CFLAGS) binomialtest.c
	$(CC) $(LFLAGS) integer.o dll.o binomial.o binomialtest.o -o bintest
test: dlltest binomialtest
	@./dlltest0
	@./dlltest1
	@./bintest
valgrind: dlltest
	@./valgrind dlltest
clean:
	@rm -rf *.o
	@rm -rf *.gch
	@rm -rf dlltest
