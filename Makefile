########################################
##
## Makefile
## LINUX compilation
##
##############################################





#FLAGS
C++FLAG = -g -std=c++0x -Wall

#Math Library
MATH_LIBS = -lm
EXEC_DIR=.





#Rule for .cpp files
# .SUFFIXES : .cpp.o

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@




#Including
INCLUDES=  -I.


LIBS_ALL =  -L/usr/lib -L/usr/local/lib $(MATH_LIBS)


#ZEROTH PROGRAM
ALL_OBJ0=NotFoundException.o main.o PreconditionViolatedException.o
PROGRAM_0=wordSearch
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

#ALL_OBJ3=NotFoundException.o MainBST.o PreconditionViolatedException.o
#PROGRAM_3=TestBSTProgram
#$(PROGRAM_3): $(ALL_OBJ3)
#	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ3) $(INCLUDES) $(LIBS_ALL)

#Compiling all

all:
	make $(PROGRAM_0)
	#make $(PROGRAM_3)


#Clean obj files

clean:
	(rm -f *.o;)



(:
