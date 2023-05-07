########################################################
#Alejandro López Martínez
#Álvaro Gutiérrez de Cabiedes Gonzalvo
########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
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


p4_e1.o: p4_e1.c bstree.h types.h vertex.h
	$(CC) $(CFLAGS) -c p4_e1.c

p4_e2.o: p4_e2.c search_queue.h types.h vertex.h
	$(CC) $(CFLAGS) -c p4_e2.c


vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

graph.o: graph.c graph.h vertex.h stack.h queue.h
	$(CC) $(CFLAGS) -c graph.c

delivery.o: delivery.c delivery.h
	$(CC) $(CFLAGS) -c delivery.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

file_utils.o: file_utils.c file_utils.h
	$(CC) $(CFLAGS) -c file_utils.c

bstree.o: bstree.c bstree.h types.h
	$(CC) $(CFLAGS) -c bstree.c

search_queue.o: search_queue.c bstree.h types.h
	$(CC) $(CFLAGS) -c search_queue.c



clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)


run:
	@echo ">>>>>>Running p4_e1"
	./p4_e1
	@echo ">>>>>>Running p4_e2"
	./p4_e2 


runv:
	@echo ">>>>>>Running p4_e1 with valgrind"
	valgrind --leak-check=full ./p4_e1
	valgrind --leak-check=full ./run_e1

	@echo ">>>>>>Running p1_e2 with valgrind"
	valgrind --leak-check=full ./p4_e2 
	valgrind --leak-check=full ./run_e2


include Makefile_ext