.DEFAULT_GOAL=all


MODULE=sockutil

DIR_BIN=bin
DIR_OBJ=obj
DIR_SRC=src
DIR_PUB_INC=include
DIR_PRI_INC=src

# source files, with directory and extension
SOURCES=$(wildcard $(DIR_SRC)/*.c)
# target names of object files, no directory
OBJECTS=$(patsubst %.c, %.o, $(notdir $(SOURCES)))
# header files (these need to be tracked too!)
HEADERS=$(wildcard $(DIR_PUB_INC)/*.h) $(wildcard $(DIR_PRI_INC)/*.h)


all: static shared

static: $(OBJECTS)
	ar rcs $(DIR_BIN)/lib$(MODULE).a $(DIR_OBJ)/$^

shared:

%.o: $(DIR_SRC)/%.c
	gcc -c $^ -o $(DIR_OBJ)/$@ -Wall

clean:
	rm -rf $(DIR_OBJ)/* $(DIR_BIN)/*

