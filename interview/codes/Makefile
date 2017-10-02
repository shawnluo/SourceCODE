FLAGS = -std=c99 -g -Wall -O


interview: interview.c
	@gcc interview.c -o interview -lm -lpthread $(FLAGS)

.PHONY: clean

clean:
	@rm interview
