CC=gcc
CFLAGS=-I.
DEPS = 
OBJ = main.o
EXECUTABLE=worldtime

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

worldtime: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

