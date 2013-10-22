CC=gcc
CFLAGS=-I.
DEPS = 
OBJ = main.o
EXECUTABLE=worldtime

%.o: %.c $(DEPS)
	$(CC) -c -g3 -O0 -o $@ $< $(CFLAGS)

worldtime: $(OBJ)
	gcc -g3 -O0 -o $@ $^ $(CFLAGS)
	
clean: 
	rm -rf *.o worldtime
	

