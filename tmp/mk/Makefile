
#CFLAGS	= -g -O3 `pkg-config opencv --cflags`  
CFLAGS	= -std=c99 -g -Wall -O -L/home/wallace/workSPACE/gitHUB/SourceCODE/tools/textColor -I/home/wallace/workSPACE/gitHUB/SourceCODE/tools/textColor/include -lpthread -lcolor

#LIBS	= `pkg-config opencv --libs`  
LIBS 	= -lpthread -lcolor 

C_SRC 	= $(wildcard *.c)  

#C_OBJ 	= $(patsubst %.c, %.o, $(C_SRC))  
C_OBJ 	= $(patsubst %.c, %, $(C_SRC))  

CPP_SRC	= $(wildcard *.cpp)
CPP_OBJ	= $(patsubst %cpp, %o, $(CPP_SRC))  
  
.PHONY:clean  
  
all:$(CPP_OBJ) $(C_OBJ)  
#	gcc -o $@ $< $(CFLAGS) $(LIBS)
#.c.o:
#	@gcc $< -o $@   $(LIBS) $(CFLAGS)
#.cpp.o:  
#	@g++ $(CFLAGS) -o $@ $< $(LIBS)  
  
  
clean:  
	@rm *~ *.o $(C_OBJ) -f  
