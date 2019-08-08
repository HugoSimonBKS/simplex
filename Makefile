CC = gcc
EXEC = simplex
CFLAGS = -Wall -Wextra -Werror
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)
	@echo "done"
	$(EXEC)

%.o: %.c
	@echo "compiling..."
	$(CC) -o $@ -c $<
