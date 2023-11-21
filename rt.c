#ifndef _WIN32
#include<termios.h>
#include<unistd.h>
#else
#include<windows.h>
#endif
int run_game(int argl, char *argv[]);
int main(int argl, char *argv[])
{
#ifndef _WIN32
    struct termios old, curr;
    tcgetattr(STDIN_FILENO, &old);
    curr = old;
    curr.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &curr);
#else
    DWORD mode;
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hout, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hout, mode);
#endif
    int succ = run_game(argl, argv);
#ifndef _WIN32
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
#endif
    return succ;
}
