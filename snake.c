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
}
int run_game(int argl, char *argv[])
{
    char alive = 1;
    unsigned arenasz = 24;
    char **arena, *displaybuf;
    struct snake_cell *head, *tail;
    struct snake_cell *tmpcell;
    struct linear_congruential_generator dice;
    long button;
    short delay = 250;
    unsigned nextx, nexty;
    unsigned fruitx = arenasz - 1, fruity = arenasz - 1;
    int dx = 1, dy = 0;
    unsigned score = 0;
    init_lcg_default(&dice);
    if(argv[1])
        arenasz = atoi(argv[1]);
    if(argl > 2)
        delay = atoi(argv[2]);
    if(arenasz < 24)
        arenasz = 24;
    displaybuf = malloc(arenasz * (arenasz + 1));
    arena = malloc_table(arenasz, arenasz, sizeof(**arena));
    tableset(arena, '.', arenasz, arenasz, sizeof(**arena));
    head = makecell(NULL, NULL, 0, 1);
    tail = makecell(head, NULL, 0, 0);
    paintsnake(arena, head);
    arena[fruity][fruitx]= '$';
    display(arena, displaybuf, arenasz);
    while(alive)
    {
        move_cursor(UP, arenasz);
        while(stdincnt() > 0)
        {
            button = keystroke();
            switch(button)
            {
                case KEY_ESC:
                    alive = 0;
                    break;
                case'W':
                case'w':
                case KEY_UP:
                    if(dy == 0)
                    {
                        dx = 0;
                        dy = -1;
                    }
                    break;
                case'A':
                case'a':
                case KEY_LEFT:
                    if(dx == 0)
                    {
                        dx = -1;
                        dy = 0;
                    }
                    break;
                case'D':
                case'd':
                case KEY_RIGHT:
                    if(dx == 0)
                    {
                        dx = 1;
                        dy = 0;
                    }
                    break;
                case'S':
                case's':
                case KEY_DN:
                    if(dy == 0)
                    {
                        dx = 0;
                        dy = 1;
                    }
                    break;
                default:
                    putchar('\a');
                    fflush(stdout);
            }
        }
        nextx = head->c + dx;
        nexty = head->r + dy;
        if(nextx >= arenasz || nextx < 0 || nexty >= arenasz || nexty < 0 || arena[nexty][nextx] == '#')
            alive = 0;
        else
        {
            head = makecell(NULL, head, nexty, nextx);
            if(head->r == fruity && head->c == fruitx)
            {
                arena[fruity][fruitx] = '#';
                while(arena[fruity][fruitx] == '#')
                {
                    fruitx = lcg_next(&dice) % arenasz;
                    fruity = lcg_next(&dice) % arenasz;
                }
                ++score;
            }
            else
            {
                tmpcell = tail;
                tail = tail->prev;
                remove_cell(tmpcell);
            }
        }
        tableset(arena, '.', arenasz, arenasz, sizeof(**arena));
        paintsnake(arena, head);
        arena[fruity][fruitx] = '$';
        display(arena, displaybuf, arenasz);
        thsleep(delay);
    }
    for(struct snake_cell *n = head, *next; n != NULL; n = next)
    {
        next = n->next;
        remove_cell(n);
    }
    printf("Your score is %u, good game!\n", score);
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
