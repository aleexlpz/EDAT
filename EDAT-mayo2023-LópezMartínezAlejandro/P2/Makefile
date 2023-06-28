########################################################
CC=gcc
CFLAGS= -g -Wall
EJS = p2_e1a p2_e2 p2_e1b
########################################################
OBJECTSP2E1A = p2_e1a.o libstack.a
OBJECTSP2E1B = p2_e1b.o libstack.a vertex.o
OBJECTSP2E2 = p2_e2.o graph.o vertex.o stack.o
########################################################

all: $(EJS) clear

p2_e1a: $(OBJECTSP2E1A)
	$(CC) $(CFLAGS) -o p2_e1a $(OBJECTSP2E1A)

p2_e1b: $(OBJECTSP2E1B)
	$(CC) $(CFLAGS) -o p2_e1b $(OBJECTSP2E1B)

p2_e2: $(OBJECTSP2E2)
	$(CC) $(CFLAGS) -o p2_e2 $(OBJECTSP2E2)



p2_e1a.o: p2_e1a.c stack.h
	$(CC) $(CFLAGS) -c p2_e1a.c

p2_e1b.o: p2_e1b.c vertex.h graph.h
	$(CC) $(CFLAGS) -c p2_e1b.c

p2_e2.o: p2_e2.c vertex.h graph.h
	$(CC) $(CFLAGS) -c p2_e2.c




vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

graph.o: graph.c graph.h vertex.h
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c




clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)


run:
	@echo ">>>>>>Running p2_e1a"
	./p2_e1a grades1.txt grades2.txt
	@echo ">>>>>>Running p2_e1b"
	./p2_e1b grades1.txt grades2.txt
	@echo ">>>>>>Running p2_e2"
	./p2_e2 g1.txt 
	

runv:
	@echo ">>>>>>Running p2_e1a with valgrind"
	valgrind --leak-check=full ./p2_e1a grades1.txt grades2.txt
	@echo ">>>>>>Running p2_e1b with valgrind"
	valgrind --leak-check=full ./p2_e1b grades1.txt grades2.txt
	@echo ">>>>>>Running p2_e2 with valgrind"
	valgrind --leak-check=full ./p2_e2 g2.txt 100 700
