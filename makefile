CC = gcc
CFLAGS = -pthread -lpthread -fopenmp -lgomp
BIN = darren UyandaMain2
OBJ = darren.o UyandaMain2.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

darren: darren.o
	$(CC) -pthread -lpthread -fopenmp -lgomp -o darren darren.o
	
UyandaMain2: UyandaMain2.o
	$(CC) -pthread -lpthread -fopenmp -lgomp -o UyandaMain2 UyandaMain2.o -lm

all: clean $(BIN)
.PHONY: clean

clean:
	rm -f $(BIN) $(OBJ)
