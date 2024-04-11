CC=gcc
CFLAGS=-Wall -g


SRC_FILES=main.c read.c suma.c common_part.c difference.c sym_diff.c is_equal.c checkSetsRelation.c
TEST_SRC_FILES=test_operations.c suma.c common_part.c difference.c sym_diff.c is_equal.c checkSetsRelation.c


EXEC=program
TEST_EXEC=test_operations


all: $(EXEC)


$(EXEC): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $^


test: $(TEST_SRC_FILES)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $^
	./$(TEST_EXEC)


check: $(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC)


clean:
	del program.exe test_operations.exe *.o


.PHONY: all test check clean