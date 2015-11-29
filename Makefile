CC=gcc
CFLAGS=-g -Wall -Werror -std=c99
LDFLAGS=-lSDL -lm
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

EXEC=trajectory_sim

all: $(EXEC)
	rm -rf *.o

trajectory_sim:$(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf $(EXEC)
	
