SRC_DIR = src
BIN_DIR = bin
EXEC = tp3
TEST_EXEC = $(patsubst %.c,%,$(wildcard $(SRC_DIR)/test*.c))

.PHONY: exec clean source test testbin

exec: source bindir
	cp $(SRC_DIR)/tp3 $(BIN_DIR)

bindir:
	mkdir -p $(BIN_DIR)

clean:
	$(MAKE) clean -C $(SRC_DIR)
	rm -rf $(BIN_DIR)

source:
	$(MAKE) -C $(SRC_DIR)

test: testbin
	for test in `ls $(BIN_DIR)/test*` ; do \
		$$test; \
	done

testbin: source bindir
	$(MAKE) test -C $(SRC_DIR)
	cp $(TEST_EXEC) $(BIN_DIR)
