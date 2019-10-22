LIBS  = -lkernel32 -luser32 -lgdi32 -lopengl32 -lpthread
CFLAGS = -g -Wall

SRC=$(wildcard *.c)
OBJ=$(basename $(SRC))

.PHONY: clean


all: ${OBJ}
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm *.o ${OBJ} 