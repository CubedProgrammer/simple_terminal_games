#include<stdio.h>
#include<unistd.h>
#include"utils.h"
#ifdef _WIN32
long
#endif
long keystroke(void)
{
    long val = 0;
    unsigned char buf[8];
    unsigned cnt = read(STDIN_FILENO, buf, sizeof buf);
    for(unsigned i = 0; i < cnt; ++i)
        val = (val << 8) | buf[i];
    return val;
}
void background_reset(void)
{
    fputs("\033\13339m", stdout);
}
void background_basic(enum basic_colour col)
{
    printf("\033\133%dm", col + 10);
}
void background(int col)
{
    int r = col >> 16 & 0xff, g = col >> 8 & 0xff, b = col & 0xff;
    printf("\033\13348;2;%d;%d;%dm", r, g, b);
}
void foreground_reset(void)
{
    fputs("\033\13349m", stdout);
}
void foreground_basic(enum basic_colour col)
{
    printf("\033\133%dm", col);
}
void foreground(int col)
{
    int r = col >> 16 & 0xff, g = col >> 8 & 0xff, b = col & 0xff;
    printf("\033\13338;2;%d;%d;%dm", r, g, b);
}
