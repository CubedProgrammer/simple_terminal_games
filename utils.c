#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#ifndef _WIN32
#include<sys/ioctl.h>
#include<unistd.h>
#else
#include<conio.h>
#include<windows.h>
#endif
#include"utils.h"
void *malloc_table(unsigned width, unsigned height, unsigned size)
{
    void *ptr = malloc(width * height * size + height * sizeof(void*));
    void **table = ptr, *tmp = table + height;
    for(unsigned i = 0; i < height; ++i)
        table[i] = (char*)tmp + i * width * size;
    return ptr;
}
void *tableset(void *ptr, int ch, unsigned width, unsigned height, unsigned size)
{
    memset((void*)((void**)ptr + height), ch, width * height * size);
    return ptr;
}
#ifdef _WIN32
long
#endif
long keystroke(void)
{
#ifdef _WIN32
    long
#endif
    long val = 0;
#ifndef _WIN32
    unsigned char buf[8];
    unsigned cnt = read(STDIN_FILENO, buf, sizeof buf);
    for(unsigned i = 0; i < cnt; ++i)
        val = (val << 8) | buf[i];
#else
    val = getch();
    switch(val)
    {
        case 0340:
            val = getch();
            switch(val)
            {
                case 0107:
                    val = KEY_HOME;
                    break;
                case 0110:
                    val = KEY_UP;
                    break;
                case 0111:
                    val = KEY_PGUP;
                    break;
                case 0113:
                    val = KEY_LEFT;
                    break;
                case 0115:
                    val = KEY_RIGHT;
                    break;
                case 0117:
                    val = KEY_END;
                    break;
                case 0120:
                    val = KEY_DN;
                    break;
                case 0121:
                    val = KEY_PGDN;
                    break;
                case 0123:
                    val = KEY_DEL;
                    break;
                case 0122:
                    val = KEY_INS;
                    break;
                case 0164:
                    val = KEY_CTRL_RIGHT;
                    break;
                case 0222:
                    val = KEY_CTRL_INS;
                    break;
                case 0163:
                    val = KEY_CTRL_LEFT;
                    break;
                case 0166:
                    val = KEY_CTRL_PGDN;
                    break;
                case 0215:
                    val = KEY_CTRL_UP;
                    break;
                case 0165:
                    val = KEY_CTRL_END;
                    break;
                case 0206:
                    val = KEY_CTRL_PGUP;
                    break;
                case 0167:
                    val = KEY_CTRL_HOME;
                    break;
                case 0223:
                    val = KEY_CTRL_DEL;
                    break;
                case 0221:
                    val = KEY_CTRL_DN;
                    break;
            }
            break;
        case 010:
            val = KEY_BACKSPACE;
            break;
        case 0:
            val = getch();
            switch(val)
            {
                case 075:
                    val = KEY_F3;
                    break;
                case 0102:
                    val = KEY_F8;
                    break;
                case 077:
                    val = KEY_F5;
                    break;
                case 0101:
                    val = KEY_F7;
                    break;
                case 0103:
                    val = KEY_F9;
                    break;
                case 0206:
                    val = KEY_F12;
                    break;
                case 0100:
                    val = KEY_F6;
                    break;
                case 0205:
                    val = KEY_F11;
                    break;
                case 074:
                    val = KEY_F2;
                    break;
                case 076:
                    val = KEY_F4;
                    break;
                case 073:
                    val = KEY_F1;
                    break;
                case 0104:
                    val = KEY_F10;
                    break;
            }
            break;
    }
#endif
    return val;
}
// Stolen from CPCDT
#ifdef _WIN32
long
#endif
long timems(void)
{
	time_t ms;
#if __STDC_VERSION__ >= 201112L
	struct timespec tm;
	timespec_get(&tm, TIME_UTC);
	ms = tm.tv_sec * 1000 + tm.tv_nsec / 1000000;
#elif defined _WIN32
	SYSTEMTIME tm;
	GetSystemTime(&tm);
	FILETIME ftm;
	SystemTimeToFileTime(&tm, &ftm);
	ULARGE_INTEGER num;
	num.LowPart = ftm.dwLowDateTime;
	num.HighPart = ftm.dwHighDateTime;
	ms = num.QuadPart;
	ms -= 116444736000000000;
	ms /= 10000;
#else
	struct timespec tm;
	clock_gettime(CLOCK_REALTIME, &tm);
	ms = tm.tv_sec * 1000 + tm.tv_nsec / 1000000;
#endif
	return ms;
}
int stdincnt(void)
{
    int cnt
#ifndef _WIN32
    ;if(ioctl(STDIN_FILENO, FIONREAD, &cnt))
        cnt = -1;
#else
    = kbhit();
#endif
    return cnt;
}
int lcg_next(struct linear_congruential_generator *gen)
{
    int num = gen->seed;
    gen->seed = gen->seed * gen->slope + gen->yint;
    gen->seed %= gen->mod;
    return num;
}
void init_lcg_default(struct linear_congruential_generator *gen)
{
    init_lcg(gen, 25214903917, 11, 281474976710656, time(NULL));
}
void init_lcg(struct linear_congruential_generator *gen, rand_t slope, rand_t yint, rand_t mod, rand_t seed)
{
    gen->slope = slope;
    gen->yint = yint;
    gen->mod = mod;
    gen->seed = seed ^ slope;
}
int thsleep(unsigned ms)
{
#ifndef _WIN32
    return usleep(ms * 1000);
#else
    Sleep(ms);
    return 0;
#endif
}
int termsz(unsigned *restrict width, unsigned *restrict height)
{
#ifndef _WIN32
    struct winsize ws;
    int succ = ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    *width = ws.ws_col;
    *height = ws.ws_row;
#else
    CONSOLE_SCREEN_BUFFER_INFO info;
    int succ = !GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    *width = info.srWindow.Right - info.srWindow.Left + 1;
    *height = info.srWindow.Bottom - info.srWindow.Top + 1;
#endif
    return succ;
}
void move_cursor(enum cursor_direction dire, unsigned cnt)
{
    printf("\033\133%u%c", cnt, dire);
}
void formatting_reset(void)
{
    fputs("\033\133m", stdout);
}
void decorate_text(enum text_decoration dec)
{
    printf("\033\133%dm", dec);
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
