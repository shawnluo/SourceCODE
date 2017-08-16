
#CFLAGS	= -g -O3 `pkg-config opencv --cflags`  
CFLAGS	= -std=c99 -g -Wall -O -L/home/wallace/workSPACE/gitHUB/SourceCODE/tools/textColor -I/home/wallace/workSPACE/gitHUB/SourceCODE/tools/textColor/include -lpthread -lcolor

#LIBS	= `pkg-config opencv --libs`  
LIBS 	= -lpthread -lcolor 

C_SRC 	= $(wildcard *.c)  

#C_OBJ 	= $(patsubst %.c, %.o, $(C_SRC))  
C_OBJ 	= $(patsubst %.c, %, $(C_SRC))  

CPP_SRC	= $(wildcard *.cpp)
CPP_OBJ	= $(patsubst %cpp, %o, $(CPP_SRC))  
  
.PHONY:all clean  
  
all:$(CPP_OBJ) $(C_OBJ)  
  
.c.o:  
	gcc $(CFLAGS) -o $@ $< $(LIBS)   
.cpp.o:  
	g++ $(CFLAGS) -o $@ $< $(LIBS)  
  
  
clean:  
	rm *~ *.o $(C_OBJ) -f  
