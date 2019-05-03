CC=g++
LD=g++
CFLAGS=-c -g -std=gnu++17 -Wall -Wextra
LFLAGS=-lGL -lglfw -lGLEW

OBJS=main.o \
	 App.o

all: main

clean:
	rm *.o main

main: $(OBJS)
	$(LD) $(LFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@
