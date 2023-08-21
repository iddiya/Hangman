# Hangman
Name of Program : main.cpp.c
As you all know, Hangman Game is a very famous word quiz program. When a word is given, it's given a blank space as long as the word length, 
and the player guesses the word by saying the alphabet one by one. I made it more difficult and difficult. 
This Demon Hangman is a specialized program for people to misspell words.


CODER: DahunIm

How to compile: 
make

CFLAGS = -g -Wall
CC = g++ -std=c++11
LDFLAGS =

BIN =    main \
  hangman \


# if make followed by no target then will compile 'Hello'
all: $(BIN) 

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@ 

$(BIN): %: %.o
	$(CC) $(CFLAGS) $@.o -o $@  $(LDFLAGS)

clean :
	-rm -f a.out *.o core atest
	-rm -f *.class
	-rm -f  $(BIN) 
    
    
How to run: 
    ./main [txtfile]
