SRC = ./src
INC = ./inc
OBJ = ./obj
BIN = ./bin
LIB = ./lib

create_obj:
	gcc -c ${SRC}/main.c -o ${OBJ}/main.o -I ${INC}
	gcc -c ${SRC}/mmath.c -o ${OBJ}/mmath.o -I ${INC}

create_static_lib:
	ar rcs lib/static/libmmath.a obj/mmath.o


linking:
	gcc ${OBJ}/main.o -L${LIB}/static/ -lmmath -o ${BIN}/use-static-library

all: create_obj create_static_lib linking
	@echo "Create Shared Library"

clean:
	rm -rf ${OBJ}/*.o
	rm -rf ${LIB}/static/libmmath.a
	rm -rf ${BIN}/use-static-library