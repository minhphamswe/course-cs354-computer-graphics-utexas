###########################################################
# Project 1 Makefile

CC = g++
CFLAGS =
#CFLAGS = -Wall -ggdb
INCLUDE =
#INCLUDE = -I/lusr/X11/include -I/lusr/include
LIBDIR =
#LIBDIR = -L/lusr/X11/lib -L/lusr/lib
# Libraries that use native graphics hardware --
# appropriate for Linux machines in Taylor basement
#LIBS = -lglut -lGLU -lGL -lpthread -lm
LIBS = -lglut -lGLU -lGL -lm

###########################################################
# Options if compiling on Mac
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
CC = g++
CFLAGS = -Wall -g -D__MAC__
INCLUDE = 
LIBDIR = -L/lusr/X11/lib
LIBS = -framework OpenGL -framework GLUT
endif

###########################################################
# Uncomment the following line if you are using Mesa
#LIBS = -lglut -lMesaGLU -lMesaGL -lm

turtle: main.o command.o point.o vector.o color.o turtle.o
	${CC} ${CFLAGS} $(INCLUDE) -o turtle main.o command.o point.o vector.o color.o turtle.o ${LIBDIR} ${LIBS}

main.o: main.cpp common.h command.h

command.o: command.cpp command.h

turtle.o: turtle.cpp turtle.h common.h geometry.h color.h

clean:
	rm -f turtle *.o
