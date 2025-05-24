
create_obj:
	gcc -c ./src/main.c -o ./obj/main.o -I ./inc/
	gcc -c -fPIC ./src/mmath.c -o ./obj/mmath.o -I ./inc/

create_shared_lib:
	gcc -shared /bin/shared/mmath.o -o ./bin/shared/libmmath.so

linking:
	gcc ./obj/main.o -L./lib/shared -lmmath -o ./bin/use-shared-library

clean:
	rm -rf ./obj/*.o