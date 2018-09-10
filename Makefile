CC ?= gcc
CFLAGS ?= -std=gnu99 -Werror -Wfatal-errors -Wall -Wextra -pedantic -Og -g -ggdb -pthread -D DEBUG= -fsanitize=address -fsanitize=leak -fsanitize=undefined
#CFLAGS ?= -O3 -std=gnu99 -Wall -pedantic

buggy: buggy.c
	rm -f buggy
	$(CC) $(CFLAGS) $< -o $@ -lm
	./buggy

buggy_OLD: buggy_OLD.c
	rm -f buggy_OLD
	$(CC) $(CFLAGS) $< -o $@ -lm
	./buggy_OLD

valgrind: 
	valgrind ./buggy

clean: 
	rm -f buggy