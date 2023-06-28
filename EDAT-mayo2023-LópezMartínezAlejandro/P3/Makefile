########################################################
CC=gcc
CFLAGS= -g -Wall
EJS =  p3_e3 p3_e2a p3_e2b  p3_e1
########################################################
OBJECTSP3E1 = p3_e1.o graph.o vertex.o stack.o delivery.o libqueue.a
OBJECTSP3E2A = p3_e2a.o graph.o vertex.o delivery.o queue.o stack.o
OBJECTSP3E2B = p3_e2b.o graph.o vertex.o queue.o stack.o
OBJECTSP3E3 = p3_e3.o list.o file_utils.o
########################################################

all: $(EJS) clear


p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1)

p3_e2a: $(OBJECTSP3E2A)
	$(CC) $(CFLAGS) -o p3_e2a $(OBJECTSP3E2A)

p3_e2b: $(OBJECTSP3E2B)
	$(CC) $(CFLAGS) -o p3_e2b $(OBJECTSP3E2B)

p3_e3: $(OBJECTSP3E3)
	$(CC) $(CFLAGS) -o p3_e3 $(OBJECTSP3E3)





p3_e1.o: p3_e1.c graph.h vertex.h delivery.h stack.o
	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2a.o: p3_e2a.c graph.h vertex.h stack.o
	$(CC) $(CFLAGS) -c p3_e2a.c

p3_e2b.o: p3_e2b.c graph.h vertex.h queue.o stack.o
	$(CC) $(CFLAGS) -c p3_e2b.c

p3_e3.o: p3_e3.c list.h file_utils.h
	$(CC) $(CFLAGS) -c p3_e3.c




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



clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)


run:
	@echo ">>>>>>Running p3_e1"
	./p3_e1 requests.txt
	@echo ">>>>>>Running p3_e2a"
	./p3_e2a requests.txt
	@echo ">>>>>>Running p3_e2b"
	./p3_e2b g2.txt 100 700 
	@echo ">>>>>>Running p3_e3"
	./p3_e3 grades.txt 1
	@echo ">>>>>>Running p3_e3"
	./p3_e3 grades.txt -1

runv:
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full ./p3_e1 requests.txt
	@echo ">>>>>>Running p3_e2a with valgrind"
	valgrind --leak-check=full ./p3_e2a requests.txt
	@echo ">>>>>>Running p3_e2b with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e2b g2.txt 100 700 
	@echo ">>>>>>Running p3_e3 with valgrind"
	valgrind --leak-check=full ./p3_e3 grades.txt 1
	@echo ">>>>>>Running p3_e3 with valgrind"
	valgrind --leak-check=full ./p3_e3 grades.txt -1
