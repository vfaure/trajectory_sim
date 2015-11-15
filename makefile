CC=gcc
CC_FLAGS=-Wall -Werror
LD_FLAGS=-lSDL
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

EXEC=trajectory_sim

all: $(EXEC)

trajectory_sim:$(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf $(EXEC)
	
