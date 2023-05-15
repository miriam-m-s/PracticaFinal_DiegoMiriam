CC = g++
CFLAGS = -Wall -Wextra
LDFLAGS = `sdl2-config --cflags --libs` -lSDL2_image

TARGET = programa
SOURCES = Renderer.cc Image.cpp Image.h GameObject.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
