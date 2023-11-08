all:connect_four.out snake.out
snake.out: utils.o snake.o
	cc -o snake.out snake.o utils.o
snake.o: snake.c
	cc -std=c99 -O3 -c snake.c
connect_four.out: utils.o connect_four.o
	cc -o connect_four.out connect_four.o utils.o
connect_four.o: connect_four.c
	cc -std=c99 -O3 -c connect_four.c
utils.o: utils.c
	cc -std=c99 -O3 -c utils.c
install:
	cp *.out /usr/local/bin
