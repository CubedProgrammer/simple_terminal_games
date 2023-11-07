all:connect_four.out
connect_four.out: utils.o connect_four.o
	cc -o connect_four.out connect_four.o utils.o
connect_four.o: connect_four.c
	cc -std=c99 -O3 -c connect_four.c
utils.o:
	cc -std=c99 -O3 -c utils.c
install:
	cp *.out /usr/local/bin
