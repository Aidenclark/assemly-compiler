CC = gcc
CFLAGS = -Wall
LIBS =
SRC = main.h
TARGET = P0
OBJ = main.o buildtree.o traversals.o

P0: $(OBJ)
	$(CC) $(CFLAGS) -o P0 $(OBJ) $(LIBS)

main.o: main.c

buildtree.o: buildtree.c

traversals.o: traversals.c

clean:
	/bin/rm -f *.o $(TARGET)