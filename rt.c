#ifndef _WIN32
#include<termios.h>
#include<unistd.h>
#else
#include<windows.h>
#endif
int run_game(int argl, char *argv[]);
int main(int argl, char *argv[])
{
    int succ;
#ifndef _WIN32
    struct termios old, curr;
    tcgetattr(STDIN_FILENO, &old);
    curr = old;
    curr.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &curr);
    if(isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
#else
    DWORD mode;
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hout, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hout, mode);
#endif
        succ = run_game(argl, argv);
#ifndef _WIN32
    else
    {
        const char errmsg[] = "Standard streams must be attached to a terminal.\n";
        write(STDERR_FILENO, errmsg, sizeof(errmsg) - 1);
        succ = 1;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
#endif
    return succ;
}
