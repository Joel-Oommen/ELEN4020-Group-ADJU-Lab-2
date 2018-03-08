CC = gcc
CFLAGS = -pthread -lpthread -fopenmp -lgomp

pthread: pthread.o
	$(CC) -pthread -lpthread -fopenmp -lgomp -o pthread pthread.o
