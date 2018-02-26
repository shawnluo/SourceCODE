FLAGS = -std=c99 -g -Wall -O


test: test.c
	@gcc test.c -o test -lm -lpthread $(FLAGS)

.PHONY: clean

clean:
	@rm test
