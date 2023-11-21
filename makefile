all:libsimple_terminal_games.so connect_four.out snake.out
snake.out: rt.o snake.o libsimple_terminal_games.so
	cc -o snake.out snake.o rt.o -L. -lsimple_terminal_games
snake.o: snake.c
	cc -std=c99 -O3 -c snake.c
connect_four.out: rt.o connect_four.o libsimple_terminal_games.so
	cc -o connect_four.out connect_four.o rt.o -L. -lsimple_terminal_games
connect_four.o: connect_four.c
	cc -std=c99 -O3 -c connect_four.c
libsimple_terminal_games.so: utils.o
	cc -shared -o libsimple_terminal_games.so utils.o
rt.o: rt.c
	cc -std=c99 -O3 -c rt.c
utils.o: utils.c
	cc -O3 -c utils.c -fPIC
install:
	cp *.out /usr/local/bin
	cp *.so /usr/local/lib
