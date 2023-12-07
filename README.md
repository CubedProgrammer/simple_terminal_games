# simple\_terminal\_games
Simple games that can be run on the command line.
## Compilation
Run `make` or compile manually.
```sh
cc -O3 -c rt.c connect_four.c snake.c
cc -O3 -c utils.c -fPIC
cc -shared -o libsimple_terminal_games.so utils.o
```
Then for every .o file that is not rt.o nor utils.o, link it with rt.o and libsimple\_terminal\_games.so to create the program.

MSVC follows a similar step.
## Installation
The makefile uses the loin command from CubedProgrammer/linux\_utility to install, if it does not exist, then do this.
```
cp *.so /usr/local/lib
for i in *.out; do
    cp ${i} /usr/local/bin/${i:0: -4};
done
```
## Games
### connect\_four
Two-player game, connect four of your symbol in a row, column or diagonal first to win.
Can be customized to have a bigger board, or require more than four to win.

Press keys 1, 2, 3, 4, 5, 6, 7, ... to drop a piece in the corresponding column.

Press space to resign.
### snake
You are snake slithering around a room, eat food by passing your head through it.
You grow longer after you eat, and new food appears elsewhere.

Arrow keys to change direction of motion.

The first argument is the size of the arena. The second is millisecond delay between moving one unit.

If the first argument is not a number, it will be a file that is used to save your score.
