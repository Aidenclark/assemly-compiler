CC = g++
CFLAGS = -Wall
LIBS =
SRC = main.h
TARGET = scanner
OBJ = main.o scanner.o testScanner.o

scanner: $(OBJ)
	$(CC) $(CFLAGS) -o scanner $(OBJ) $(LIBS)

main.o: main.cpp

scanner.o: scanner.cpp

testScanner.o: testScanner.cpp

clean:
	/bin/rm -f *.o $(TARGET)