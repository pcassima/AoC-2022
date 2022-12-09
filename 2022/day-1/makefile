CC=gcc
TARGET=solution
default: all

main.o: main.c
	cc -c main.c -o main.o

all: main.o
	cc main.o -o $(TARGET)

clean:
	rm $(TARGET)
	rm main.o
