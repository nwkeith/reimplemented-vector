CC = g++
CFLAGS = -g -Wall  -std=c++17

all: tests

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp 

TemplateUnitTests.o: TemplateUnitTests.cpp
	$(CC) $(CFLAGS) -c TemplateUnitTests.cpp

IntUnitTests.o: IntUnitTests.cpp
	$(CC) $(CFLAGS) -c IntUnitTests.cpp

tests: main.o TemplateUnitTests.o IntUnitTests.o
	$(CC) $(CFLAGS) -o tests main.o TemplateUnitTests.o IntUnitTests.o

clean:
	rm -rf *o tests 
