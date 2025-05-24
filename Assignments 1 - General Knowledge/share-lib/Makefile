
create_obj:
	gcc -c ./src/main.c -o ./obj/main.o -I ./inc/
	gcc -c -fPIC ./src/mmath.c -o ./obj/mmath.o -I ./inc/

create_shared_lib:
	gcc -shared ./obj/mmath.o -o ./lib/shared/libmmath.so

linking:
	gcc ./obj/main.o -L./lib/shared/ -lmmath -o ./bin/use-shared-library

all: create_obj create_shared_lib linking
	@echo "Create Shared Library"

clean:
	rm -rf ./obj/*.o
	rm -rf ./lib/shared/libmmath.so
	rm -rf ./bin/use-shared-library