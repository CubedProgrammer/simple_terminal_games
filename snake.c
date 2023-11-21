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
        if(prev != NULL)
            prev->next = cell;
        if(next != NULL)
            next->prev = cell;
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
void paintsnake(char **ptr, struct snake_cell *head)
{
    for(struct snake_cell *node = head; node != NULL; node = node->next)
        ptr[node->r][node->c] = '#';
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
    fflush(stdout);
    move_cursor(UP, arenasz);
}
int run_game(int argl, char *argv[])
{
    char alive = 1;
    unsigned arenasz = 24;
    char **arena, *displaybuf;
    struct snake_cell *head, *tail;
    long button;
    int dx, dy;
    if(argv[1])
        arenasz = atoi(argv[1]);
    if(arenasz < 24)
        arenasz = 24;
    displaybuf = malloc(arenasz * (arenasz + 1));
    arena = malloc_table(arenasz, arenasz, sizeof(**arena));
    tableset(arena, '.', arenasz, arenasz, sizeof(**arena));
    head = makecell(NULL, NULL, 0, 1);
    tail = makecell(head, NULL, 0, 0);
    paintsnake(arena, head);
    display(arena, displaybuf, arenasz);
    while(alive)
    {
        while(stdincnt() > 0)
        {
            dy = dx = 0;
            button = keystroke();
            switch(button)
            {
                case KEY_ESC:
                    alive = 0;
                    break;
                case KEY_UP:
                    dy = -1;
                    break;
                case KEY_LEFT:
                    dx = -1;
                    break;
                case KEY_RIGHT:
                    dx = 1;
                    break;
                case KEY_DN:
                    dy = 1;
                    break;
                default:
                    putchar('\a');
                    fflush(stdout);
            }
            if(dx + dy)
            {
                head = makecell(NULL, head, head->r + dy, head->c + dx);
                paintsnake(arena, head);
            }
        }
        display(arena, displaybuf, arenasz);
        thsleep(50);
    }
    for(struct snake_cell *n = head, *next; n != NULL; n = next)
    {
        next = n->next;
        remove_cell(n);
    }
    return 0;
}
