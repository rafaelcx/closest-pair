CC = g++
LIBS += -lm

# the executable is made from one or more object files
# if you have more, add them here
closest: closest.o
	$(CC) closest.o  -o closest $(LIBS)
# an object file is made from one sourcecode file)
# if you have more, add more of these constructs
closest.o: closest.c
	$(CC) -c closest.c

clean: 
	rm *.o
	rm closest