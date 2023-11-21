all:libsimple_terminal_games.so connect_four.out snake.out
libsimple_terminal_games.so:
	cc -shared -o libsimple_terminal_games.so utils.o
snake.out: rt.o snake.o
	cc -o snake.out snake.o rt.o -L. -lsimple_terminal_games
snake.o: snake.c
	cc -std=c99 -O3 -c snake.c
connect_four.out: rt.o connect_four.o
	cc -o connect_four.out connect_four.o rt.o -L. -lsimple_terminal_games
connect_four.o: connect_four.c
	cc -std=c99 -O3 -c connect_four.c
rt.o: rt.c
	cc -std=c99 -O3 -c rt.c
utils.o: utils.c
	cc -std=c99 -O3 -c utils.c -fPIC
install:
	cp *.out /usr/local/bin
	cp *.so /usr/local/lib
