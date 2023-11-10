#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"utils.h"
struct snake_cell
{
    struct snake_cell *prev, *next;
    unsigned r, c;
};
struct snake_cell *makecell(struct snake_cell *prev, struct snake_cell *next, unsigned r, unsigned c)
{
    struct snake_cell *cell = malloc(sizeof(*cell));
    if(cell != NULL)
    {
        cell->prev = prev;
        cell->next = next;
        cell->r = r;
        cell->c = c;
    }
    return cell;
}
void insert_cell(struct snake_cell *curr, struct snake_cell *new)
{
    new->next = curr->next;
    new->prev = curr;
    curr->next = new;
    if(new->next != NULL)
        new->next->prev = new;
}
void remove_cell(struct snake_cell *cell)
{
    if(cell->prev != NULL)
        cell->prev->next = cell->next;
    if(cell->next != NULL)
        cell->next->prev = cell->prev;
    free(cell);
}
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
    struct snake_cell *head, *tail;
    if(argv[1])
        arenasz = atoi(argv[1]);
    if(arenasz < 24)
        arenasz = 24;
    displaybuf = malloc(arenasz * (arenasz + 1));
    arena = malloc_table(arenasz, arenasz, sizeof(**arena));
    tableset(arena, '.', arenasz, arenasz, sizeof(**arena));
    display(arena, displaybuf, arenasz);
    for(struct snake_cell *n = head, *next; n != NULL; n = next)
    {
        next = n->next;
        remove_cell(n);
    }
    return 0;
}
