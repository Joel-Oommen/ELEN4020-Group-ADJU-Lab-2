CC = gcc
CFLAGS = -pthread -lpthread -fopenmp -lgomp
BIN = OpenMP Pthread
OBJ = OpenMp.o Pthread.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

OpenMp: OpenMp.o
	$(CC) -pthread -lpthread -fopenmp -lgomp -o OpenMp OpenMp.o
	
Pthread: Pthread.o
	$(CC) -pthread -lpthread -fopenmp -lgomp -o Pthread Pthread.o -lm

all: $(BIN)
.PHONY: clean

clean:
	rm -f $(BIN) $(OBJ)
