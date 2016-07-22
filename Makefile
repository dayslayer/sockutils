.DEFAULT_GOAL=all


DIR_BIN=bin
DIR_OBJ=obj
DIR_SRC=src

OBJECTS=$(wildcard $(DIR_OBJ)/*.o)


all: static shared

static: $(OBJECTS)
	ar rcs $(DIR_BIN)/libsockutil.a $(OBJECTS)
shared:

%.o: $(DIR_SRC)/%.c
	gcc -c $^ -o $(DIR_OBJ)/$@ -Wall

clean:
	rm -rf $(DIR_OBJ)/* $(DIR_BIN)/*

