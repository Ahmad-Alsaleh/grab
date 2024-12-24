CC = gcc
CFLAGS = -Wall -g
LDFLAGS = 

.PHONY: run compile

run: compile
	@echo && echo -n 'Running '
	./main

compile: clean main
	make clean > /dev/null

main: main.o network.o operations.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

network.o: network.c network.h
	$(CC) $(CFLAGS) -c $<

operations.o: operations.c operations.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
