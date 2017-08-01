object = 1_typedef
CFLAGS = -g

all: $(object)
$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm $(object)
