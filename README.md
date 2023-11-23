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
