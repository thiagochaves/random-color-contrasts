CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -O2
LDFLAGS = -lm
TARGET = random-color-contrasts

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

TEST_BIN = test/test_main

$(TEST_BIN): test/test_main.c test/test_helpers.h main.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

test: $(TARGET) $(TEST_BIN)
	./$(TEST_BIN)
	node test/parity.js
	sh test/smoke.sh

clean:
	rm -f $(TARGET) $(TEST_BIN)

.PHONY: all test clean