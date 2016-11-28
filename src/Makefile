CC = gcc
CFLAGS = -g -Wall `pkg-config --cflags cairo`
LFLAGS = `pkg-config --libs cairo` 
EXEC = tp3
TEST_IMPL = $(wildcard test*.c)
AUXI_IMPL = $(filter-out $(TEST_IMPL) $(EXEC).c,$(wildcard *.c))
AUXI_OBJS = $(patsubst %.c,%.o,$(AUXI_IMPL))
TEST_OBJS = $(patsubst %.c,%.o,$(TEST_IMPL))
TEST_EXEC = $(patsubst %.c,%,$(TEST_IMPL))

$(EXEC): $(AUXI_OBJS) $(EXEC).o
	$(CC) $(LFLAGS) -o $(EXEC) $(EXEC).o $(AUXI_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean test

clean:
	rm -f *.o
	rm -rf $(EXEC)

test: $(TEST_EXEC)

$(TEST_EXEC): $(AUXI_OBJS) $(TEST_OBJS)
	$(CC) $(LFLAGS) -lcunit -o $@ $(AUXI_OBJS) $(TEST_OBJS)
