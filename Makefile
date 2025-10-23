CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -g -O1
TARGET  := lru
SRC     := main.c comandos.c funciones.c
OBJ     := $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) -f $(OBJ) $(TARGET)

.PHONY: all clean