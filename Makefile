build:
		gcc -std=c99 -Wall ./lib/lua/src/*.c ./src/main.c -lm -lSDL2 -o ./bin/main

clean:
		rm ./bin/main

run:
		./bin/main