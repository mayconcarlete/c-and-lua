build:
		gcc -std=c99 -Wall ./lib/lua/src/*.c ./src/*.c -lm -o ./bin/main

clean:
		rm ./bin/main

run:
		./bin/main