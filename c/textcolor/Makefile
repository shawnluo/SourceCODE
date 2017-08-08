all: textcolor demo
	@echo "compile"
	
textcolor: textcolor.c
	gcc textcolor.c -o textcolor
	gcc -c -fpic textcolor.c
	gcc -shared -o libcolor.so textcolor.o

demo: demo.c
	gcc demo.c -o demo -L. -lcolor

.PHONY: clean
	
clean:
	rm demo textcolor textcolor.o