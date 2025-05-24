SRC = ./src
INC = ./inc
OBJ = ./obj
BIN = ./bin
LIB = ./lib

create_obj:
	gcc -c ${SRC}/main.c -o ${OBJ}/main.o -I ${INC}
	gcc -c -fPIC ${SRC}/mmath.c -o ${OBJ}/mmath.o -I ${INC}

create_shared_lib:
	gcc -shared ${OBJ}/mmath.o -o ${LIB}/shared/libmmath.so

linking:
	gcc ${OBJ}/main.o -L${LIB}/shared/ -lmmath -o ${BIN}/use-shared-library

all: create_obj create_shared_lib linking
	@echo "Create Shared Library"

clean:
	rm -rf ${OBJ}*.o
	rm -rf ${LIB}/shared/libmmath.so
	rm -rf ${BIN}/use-shared-library