#ifndef Included_utils_h
#define Included_utils_h
enum basic_colour
{   BLACK = 30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE   };
int run_game(int argl, char *argv[]);
#ifdef _WIN32
long
#endif
long keystroke(void);
void background_reset(void);
void background_basic(enum basic_colour col);
void background(int col);
void foreground_reset(void);
void foreground_basic(enum basic_colour col);
void foreground(int col);
#endif
