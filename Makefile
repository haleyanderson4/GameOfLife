BUILD_FLAGS = -W -Wall -pedantic 
CC = g++
RM = rm
OUT = *.out

all: main.out

Bacteria.o: Makefile Bacteria.cpp
	$(CC) $(BUILD_FLAGS) -c Bacteria.cpp -o Bacteria.o

Mode.o: Makefile Mode.cpp
	$(CC) $(BUILD_FLAGS) -c Mode.cpp -o Mode.o

World.o: Makefile World.cpp
	$(CC) $(BUILD_FLAGS) -c World.cpp -o World.o

main.out: Makefile World.o Bacteria.o main.cpp
	$(CC) $(BUILD_FLAGS) World.o Bacteria.o Mode.o main.cpp -o main.out

clean:
	$(RM) $(OUT) $(OBJECTS)