CC = g++
CFLAGS = -g -Wall

all: vector

vector: main.o TemplateUnitTests.o IntUnitTests.o
	$(CC) $(CFLAGS) -o main main.o TemplateUnitTests.o IntUnitTests.o

main.o: main.cpp
	$(CC) -c main.cpp 

TemplateUnitTests.o: TemplateUnitTests.cpp
	$(CC) -c TemplateUnitTests.cpp

IntUnitTests.o: IntUnitTests.cpp
	$(CC) -c IntUnitTests.cpp

clean:
	rm -rf *o vector
