#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utils.h"
void display(char **ptr, char *buf, unsigned arenasz)
{
    unsigned ind = 0;
    for(unsigned i = 0; i < arenasz; ++i)
    {
        for(unsigned j = 0; j < arenasz; ++j)
        {
            buf[ind] = ptr[i][j];
            ++ind;
        }
        buf[ind++] = '\n';
    }
    fwrite(buf, 1, ind, stdout);
    move_cursor(UP, arenasz);
}
int run_game(int argl, char *argv[])
{
    unsigned arenasz = 24;
    char **arena, *displaybuf;
    if(argv[1])
        arenasz = atoi(argv[1]);
    if(arenasz < 24)
        arenasz = 24;
    displaybuf = malloc(arenasz * (arenasz + 1));
    arena = malloc_table(arenasz, arenasz, sizeof(**arena));
    tableset(arena, '.', arenasz, arenasz, sizeof(**arena));
    display(arena, displaybuf, arenasz);
    return 0;
}
