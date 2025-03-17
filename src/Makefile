CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Werror -std=c11
GFLAGS =
LFLAGS = -lcheck -lsubunit -lm -l:s21_string.a

BUILD_DIR = s21_report_g

LIB = s21_string.a

EXEC = s21_test

SOURCES = $(wildcard functions/*.c)
OBJECTS = $(SOURCES:.c=.o)

TEST_SOURCES = $(wildcard tests/*.c)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

.PHONY: clean test gcov_report

all: s21_string.a

$(EXEC): $(TEST_OBJECTS) $(LIB)
	$(CC) $(CFLAGS) $(TEST_OBJECTS) -o $(EXEC) -L. -l:s21_string.a $(LFLAGS)

test: LFLAGS += -lgcov
test: GFLAGS += --coverage
test: $(EXEC)
	./$(EXEC)

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

functions/%.o: functions/%.c
	$(CC) $(CFLAGS) $(GFLAGS) -c $< -o $@

$(LIB): $(OBJECTS)
	ar -rcs $@ $(OBJECTS)

gcov_report: test
	mkdir $(BUILD_DIR)
	lcov -c -d . -o $(BUILD_DIR)/coverage.info
	genhtml $(BUILD_DIR)/coverage.info --output-directory $(BUILD_DIR)
	xdg-open $(BUILD_DIR)/index.html

clean:
	rm -f $(EXEC)
	rm -f *.a **/*.o
	rm -f **/*.gcno **/*.gcda **/*.gcov
	rm -rf $(BUILD_DIR)
 
check:
	clang-format -n **/*.c **/*.h *.c *.h
    
val: $(EXEC)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(EXEC)

open:
	xdg-open s21_report/s21_string.html

main:
	@$(CC) $(CFLAGS) *.c s21_string/*.c -o main -lm
	@./main
	@make clean