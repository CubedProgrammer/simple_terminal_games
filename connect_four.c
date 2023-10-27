#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utils.h"
char play(char *board, unsigned width, unsigned height, unsigned col, char c)
{
    char succ = 0;
    unsigned r;
    for(r = 0; board[r * width + col] == ' ' && r < height; ++r);
    if(r != 0)
    {
        succ = 1;
        board[--r * width + col] = c;
    }
    return succ;
}
void display(char *board, unsigned width, unsigned height)
{
    for(unsigned r = 0; r < height; ++r)
    {
        fwrite(board + r * width, 1, width, stdout);
        putchar('\n');
    }
}
int run_game(int argl, char *argv[])
{
    unsigned defaultv[3] = {7, 6, 4};
    unsigned width, height, require;
    unsigned area;
    char *board;
    const char playerch[] = "XO";
    char currplayer = 0;
    if(argl > 4)
        argl = 4;
    for(int i = 1; i < argl; ++i)
        defaultv[i] = atoi(argv[i]);
    width = defaultv[0], height = defaultv[1];
    require = defaultv[2];
    area = width * height;
    board = malloc(area * sizeof(*board));
    memset(board, ' ', area * sizeof(*board));
    display(board, width, height);
    for(long k = keystroke(); k != 033; k = keystroke())
    {
        if(k >= '1' && k <= '9')
            k -= '1';
        else if(k == '0')
            k = 9;
        else if(k >= 'A' && k <= 'Z')
            k -= 'A' - 10;
        else if(k >= 'a' && k <= 'z')
            k -= 'a' - 10;
        if(play(board, width, height, k, playerch[currplayer]))
        {
            currplayer = !currplayer;
            move_cursor(UP, height);
            display(board, width, height);
        }
    }
    free(board);
    return 0;
}
