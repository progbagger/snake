CC = gcc
CFLAGS = -Wall -Werror -Wextra
MAIN = main.c
CFILES = game.c queue.c snake.c
OBJECTS = $(CFILES:.c=.o)
EXEC = snake
P = ../build/

all: build clean

build: $(EXEC)

$(EXEC): $(MAIN) $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(P)$(EXEC)

$(OBJECTS): $(CFILES)
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *.o *.gch *.out

clean_exe:
	rm -rf ../build/[!.gitkeep]*

force_clean: clean clean_exe