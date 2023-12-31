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
int ucomparcv(const void *x, const void *y)
{
    unsigned m = *(const unsigned*)x;
    unsigned n = *(const unsigned*)y;
    return m > n ? 1 : m < n ? -1 : 0;
}
unsigned ubsearch(const unsigned *arr, unsigned len, unsigned target)
{
    unsigned hi = len - 1, lo = 0;
    unsigned mid;
    while(hi > lo)
    {
        mid = (hi + lo) / 2;
        if(arr[mid] < target)
            lo = mid + 1;
        else
            hi = mid;
    }
    if(arr[lo] < target)
        return len;
    else
        return lo;
}
int run_game(int argl, char *argv[])
{
    char alive = 1;
    unsigned arenasz = 24;
    char **arena, *displaybuf;
    char *scorefile = NULL;
    FILE *scorefh = NULL;
    struct snake_cell *head, *tail;
    struct snake_cell *tmpcell;
    struct linear_congruential_generator dice;
    long button;
    short delay = 250;
    unsigned width, height, length;
    unsigned nextx, nexty;
    unsigned fruitx = 0, fruity = 1;
    int dx = 1, dy = 0;
    unsigned score = 0;
    unsigned currscore;
    unsigned *scorearr = NULL, *tmparr;
    unsigned scorelen = 0, scorecapa = 8;
    unsigned scorerank;
    init_lcg_default(&dice);
    termsz(&width, &height);
    length = width < height ? width : height;
    length -= 2;
    if(argv[1])
    {
        if(argv[1][0] > '9' || argv[1][9] < '0')
        {
            scorefile = argv[1];
            scorefh = fopen(scorefile, "r");
            if(scorefh == NULL)
            {
                fprintf(stderr, "Failed to open %s", scorefile);
                perror("");
            }
            else
            {
                scorearr = malloc(scorecapa * sizeof(*scorearr));
                while(fscanf(scorefh, "%u", &currscore) == 1)
                {
                    if(scorelen == scorecapa)
                    {
                        tmparr = malloc((scorecapa + (scorecapa >> 1)) * sizeof(*tmparr));
                        if(tmparr == NULL)
                            perror("malloc failed");
                        else
                        {
                            scorecapa += scorecapa >> 1;
                            memcpy(tmparr, scorearr, scorelen * sizeof(unsigned));
                            free(scorearr);
                            scorearr = tmparr;
                        }
                    }
                    scorearr[scorelen] = currscore;
                    ++scorelen;
                }
                qsort(scorearr, scorelen, sizeof(*scorearr), ucomparcv);
                fclose(scorefh);
            }
            ++argv;
        }
    }
    if(argv[1])
        arenasz = atoi(argv[1]);
    if(argl > 2)
        delay = atoi(argv[2]);
    if(arenasz < 24)
        arenasz = 24;
    if(length < 24)
        fputs("Your window is too small, please make it bigger.\n", stderr);
    else if(length < arenasz)
        fprintf(stderr, "You requested an arena size of %u, but your window is only %u by %u.\n", arenasz, width, height);
    else
    {
        displaybuf = malloc(arenasz * (arenasz + 1));
        arena = malloc_table(arenasz, arenasz, sizeof(**arena));
        tableset(arena, '.', arenasz, arenasz, sizeof(**arena));
        head = makecell(NULL, NULL, 0, 1);
        tail = makecell(head, NULL, 0, 0);
        paintsnake(arena, head);
        arena[fruity][fruitx]= '$';
        puts("Use WASD or arrow keys to change direction, press once and do not hold. You cannot stop moving or reverse.");
        puts("Eat to grow longer, hitting a wall or yourself is death.");
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
        if(score == 0)
            puts("You did not grow at all this game, better luck next time!");
        else
            printf("Your score is %u, good game!\n", score);
        if(scorefile != NULL)
        {
            scorerank = ubsearch(scorearr, scorelen, score + 1);
            scorerank = scorelen - scorerank + 1;
            if(scorerank == 1)
                puts("All time high!");
            else
                printf("%uth place of all time.\n", scorerank);
            free(scorearr);
            scorefh = fopen(scorefile, "a");
            if(scorefh == NULL)
            {
                fprintf(stderr, "Failed to open %s", scorefile);
                perror("");
            }
            else
            {
                fprintf(scorefh, "%u\n", score);
                fclose(scorefh);
            }
        }
#ifdef _WIN32
        system("pause");
#endif
    }
    return 0;
}
