

CPPFLAGS = -fPIC
LDFLAGS = -shared

FLAGS = -I./include

all: textcolor textcolor.o libcolor.so demo
	@echo "compile"
	
textcolor: textcolor.c
	gcc textcolor.c -o textcolor $(FLAGS)
	#/home/wallace/workSPACE/gitHUB/SourceCODE/tools/textColor/include

textcolor.o:
	gcc -fPIC -c textcolor.c $(FLAGS)
	#/home/wallace/workSPACE/gitHUB/SourceCODE/tools/textColor/include

libcolor.so:
	gcc -shared -o libcolor.so textcolor.o $(FLAGS)
	#-I/home/wallace/workSPACE/gitHUB/SourceCODE/tools/textColor/include

demo: demo.c
	gcc demo.c -o demo -L. -lcolor $(FLAGS)
	#/home/wallace/workSPACE/gitHUB/SourceCODE/tools/textColor/include

.PHONY: clean
	
clean:
	rm demo textcolor textcolor.o libcolor.so
