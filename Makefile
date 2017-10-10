SRC_DIR = src
BIN_DIR = bin
EXEC = tp2
BATS_DIR = bats
BATS_TESTS = $(wildcard $(BATS_DIR)/*.bats)
TEST_EXEC = $(patsubst %.c,%,$(wildcard $(SRC_DIR)/test*.c))

.PHONY: exec clean source test testbats testbin testcunit

exec: source bindir
	cp $(SRC_DIR)/tp2 $(BIN_DIR)

bindir:
	mkdir -p $(BIN_DIR)

clean:
	$(MAKE) clean -C $(SRC_DIR)
	rm -rf $(BIN_DIR)

source:
	$(MAKE) -C $(SRC_DIR)

test: exec testbin testcunit testbats

testbats:
	bats $(BATS_TESTS)

testbin: source bindir
	$(MAKE) test -C $(SRC_DIR)
	cp $(TEST_EXEC) $(BIN_DIR)

testcunit:
	for test in `ls $(BIN_DIR)/test*` ; do \
		$$test; \
	done
