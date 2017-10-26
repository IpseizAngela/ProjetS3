SRC=breakout.c
BIN=breakout

$(BIN): $(SRC) object_breakout.o
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs` -lSDL_ttf -o $(BIN) object_breakout.o -lm

object_breakout.o : object_breakout.c object_breakout.h
	gcc -Wall -Wextra -pedantic -g -std=c99 -c `sdl-config --cflags --libs` -lm -O3 -lSDL_ttf object_breakout.c -g

clean:
	rm -f $(BIN)
