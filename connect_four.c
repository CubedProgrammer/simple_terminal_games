#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utils.h"
char keystrokes[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char getres(char *board, unsigned width, unsigned height, unsigned require)
{
    char res = 0, eq;
    char full = 1;
    unsigned ind;
    for(unsigned i = 0; res == 0 && i < height; ++i)
    {
        for(unsigned j = 0; res == 0 && j < width - require + 1; ++j)
        {
            ind = i * width + j;
            eq = board[i * width + j] != ' ';
            for(unsigned k = 1; eq && k < require; ++k)
                eq = board[ind] == board[ind + k];
            if(eq)
                res = board[ind];
        }
    }
    for(unsigned i = 0; res == 0 && i < height - require + 1; ++i)
    {
        for(unsigned j = 0; res == 0 && j < width; ++j)
        {
            ind = i * width + j;
            eq = board[i * width + j] != ' ';
            for(unsigned k = 1; eq && k < require; ++k)
                eq = board[ind] == board[ind + k * width];
            if(eq)
                res = board[ind];
        }
    }
    for(unsigned i = 0; res == 0 && i < height - require + 1; ++i)
    {
        for(unsigned j = 0; res == 0 && j < width - require + 1; ++j)
        {
            ind = i * width + j;
            eq = board[i * width + j] != ' ';
            for(unsigned k = 1; eq && k < require; ++k)
                eq = board[ind] == board[ind + k * width + k];
            if(eq)
                res = board[ind];
        }
    }
    for(unsigned i = 0; full && i < height; ++i)
    {
        for(unsigned j = 0; full && j < width; ++j)
            full = board[i * width + j] != ' ';
    }
    if(!res)
        res = full;
    return res;
}
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
    fwrite(keystrokes, 1, width + 1, stdout);
}
int run_game(int argl, char *argv[])
{
    unsigned defaultv[3] = {7, 6, 4};
    unsigned tw, th;
    unsigned width, height, require;
    unsigned area;
    char result = 0;
    char *board;
    const char playerch[] = "XO";
    char surrender = 0;
    char currplayer = 0;
    if(argl > 4)
        argl = 4;
    for(int i = 1; i < argl; ++i)
        defaultv[i - 1] = maxl(defaultv[i - 1], atoi(argv[i]));
    width = defaultv[0], height = defaultv[1];
    require = defaultv[2];
    termsz(&tw, &th);
    if(width > tw || height > th)
    {
        fprintf(stderr, "Your terminal is %u by %u, but you requested a %u by %u board size.\n", tw, th, width, height);
        width = 7;
        height = 6;
        require = 4;
    }
    if(require > width || require > height)
    {
        fprintf(stderr, "%u is too big for a %u by %u board.\n", require, width, height);
        require = minl(width, height);
        fprintf(stderr, "You need %u in a row to win instead.\n", require);
    }
    area = width * height;
    board = malloc(area * sizeof(*board));
    memset(board, ' ', area * sizeof(*board));
    if(width > 36)
    {
        fprintf(stderr, "Width of %u is too high, maximum is 36.\n", width);
        width = 36;
    }
    keystrokes[width] = '\n';
    display(board, width, height);
    for(long k = keystroke(); k != KEY_ESC; k = result == 0 ? keystroke() : 033)
    {
        if(k >= '1' && k <= '9')
            k -= '1';
        else if(k == '0')
            k = 9;
        else if(k >= 'A' && k <= 'Z')
            k -= 'A' - 10;
        else if(k >= 'a' && k <= 'z')
            k -= 'a' - 10;
        else if(k == ' ')
            k = width;
        if(k == width)
        {
            surrender = 1;
            result = playerch[currplayer];
        }
        else if(play(board, width, height, k, playerch[currplayer]))
        {
            currplayer = !currplayer;
            move_cursor(UP, height + 1);
            display(board, width, height);
        }
        if(result == 0)
            result = getres(board, width, height, require);
    }
    if(result == 1)
        puts("Draw!");
    else if(result != 0)
    {
        if(surrender)
            printf("%c has resigned the game.\n", result);
        else
            printf("%c has won the game.\n", result);
    }
    free(board);
    return 0;
}
