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
