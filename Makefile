CC = /usr/bin/g++
CCFLAGS = -Wpedantic -Wall -Wextra -Werror -Wno-sign-compare -Wno-implicit-fallthrough

OBJECTS = State.o InputTape.o TuringMachine.o 

all: ttm

ttm: main.cpp $(OBJECTS)	
	$(CC) $(CCFLAGS) -o $@ $^

InputTape.o: InputTape.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

State.o: State.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

TuringMachine.o: TuringMachine.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -fv $(OBJECTS) ttm

