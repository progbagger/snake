CC = gcc
CFLAGS = -Wall -Werror -Wextra
EXEC = snake

all: $(EXEC)

$(EXEC): main.c snake.o
	$(CC) $(CFLAGS) main.c snake.o -o ../build/$(EXEC)

snake.o: snake.c snake.h
	$(CC) $(CFLAGS) -c snake.c

clean:
	rm -rf *.o *.out ../build/snake