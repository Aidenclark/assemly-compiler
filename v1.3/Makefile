CC = g++
CFLAGS = -g -Wall -std=c++11
OBJS = main.o testTree.o parser.o scanner.o statSem.o
DEPS = testTree.h parser.h scanner.h node.h token.h statSem.h
TARGET = statSem

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
  
$(OBJS): %.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<
  

# clean up generated files
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)