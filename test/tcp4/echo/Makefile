.DEFAULT_GOAL=all

DIR_ROOT=../../..
DIR_OBJ=$(DIR_ROOT)/obj

all: $(DIR_OBJ)/sockutils.o
	gcc -Wall -o bin/echo-client src/echo-client.c $(DIR_OBJ)/sockutils.o

