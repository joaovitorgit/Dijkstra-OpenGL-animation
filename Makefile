CC = g++

GLLIBS = -lglut -lGL -lGLU -lGLEW

all: dijkstra.c
	$(CC) dijkstra.c -o dijkstra $(GLLIBS)

clean:
	rm -f temp
