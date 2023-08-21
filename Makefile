CFLAGS = -g -Wall
CC = g++ -std=c++11
LDFLAGS =

hangman: hangman.o main.o
	$(CC) $(CFLAGS) -o hangman hangman.o main.o $(LDFLAGS)

hangman.o: hangman.cpp main.h
	$(CC) $(CFLAGS) -c hangman.cpp

main.o: main.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	-rm -f hangman
	-rm -f hangman.o
	-rm -f main.o