########################################################
#Alejandro López Martínez
#Álvaro Gutiérrez de Cabiedes Gonzalvo
########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic #-ansi
EJS = p4_e1 p4_e2 
########################################################
OBJECTSP4E1 = p4_e1.o bstree.o vertex.o
OBJECTSP4E2 = p4_e2.o search_queue.o vertex.o bstree.o
########################################################

all: $(EJS) clear


p4_e1: $(OBJECTSP4E1)
	$(CC) $(CFLAGS) -o p4_e1 $(OBJECTSP4E1)

p4_e2: $(OBJECTSP4E2)
	$(CC) $(CFLAGS) -o p4_e2 $(OBJECTSP4E2)


p4_e1.o: p4_e1.c bstree.h vertex.h
	$(CC) $(CFLAGS) -c p4_e1.c

p4_e2.o: p4_e2.c search_queue.h vertex.h
	$(CC) $(CFLAGS) -c p4_e2.c


vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

bstree.o: bstree.c bstree.h types.h
	$(CC) $(CFLAGS) -c bstree.c

search_queue.o: search_queue.c bstree.h types.h
	$(CC) $(CFLAGS) -c search_queue.c






clear:
	rm -rf *.o 
	rm -rf out/*.out

clean:
	rm -rf *.o $(EJS)

include Makefile_ext