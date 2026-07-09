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
	sh test/smoke.sh

clean:
	rm -f $(TARGET) $(TEST_BIN)
	rm -f *.gcno *.gcda *.gcov

coverage: test/test_main.c test/test_helpers.h main.c
	$(CC) $(CFLAGS) --coverage -o $(TEST_BIN) test/test_main.c $(LDFLAGS)
	./$(TEST_BIN) > /dev/null
	gcov -b -c test/test_main.c
	rm -f $(TEST_BIN) *.gcno *.gcda *.gcov

.PHONY: all test coverage clean