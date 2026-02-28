TARGET=firevm
LIBS=-lm
CC=g++
CFLAGS=-g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

FILES=$(wildcard src/*.c)
HEADERS=$(wildcard src/*.h)
OBJECTS=$(FILES:.c=.o)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	 rm -f src/*.o
	 rm -f $(TARGET)