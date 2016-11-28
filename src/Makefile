CC = gcc
CFLAGS = -Wall `pkg-config --cflags cairo`
LFLAGS = `pkg-config --libs cairo` 
EXEC = tp3
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

$(EXEC): $(OBJS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean

clean:
	rm -f *.o
	rm -rf $(EXEC)
