CC=g++
LD=g++
CFLAGS=-c -g -std=gnu++17 -Wall -Wextra
LFLAGS=-lGL -lglfw -lGLEW -lpthread

OBJS=main.o \
	 App.o \
	 graphics/Shader.o \
	 graphics/Texture.o \
	 graphics/Mesh.o \

TARGET=main


all: $(TARGET)

clean:
	rm $(OBJS) main

$(TARGET): $(OBJS)
	$(LD) $(LFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@
