#ifndef Included_utils_h
#define Included_utils_h
#define KEY_ESC 033
enum basic_colour
{   BLACK = 30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE   };
enum text_decoration
{   BOLD = 1, FAINT, ITALIC, UNDERLINE, STRIKE = 9, OVERLINE = 53   };
enum cursor_direction
{   UP = 'A', DOWN, RIGHT, LEFT   };
int run_game(int argl, char *argv[]);
#ifdef _WIN32
long
#endif
long keystroke(void);
void move_cursor(enum cursor_direction dire, unsigned cnt);
void formatting_reset(void);
void decorate_text(enum text_decoration dec);
void background_reset(void);
void background_basic(enum basic_colour col);
void background(int col);
void foreground_reset(void);
void foreground_basic(enum basic_colour col);
void foreground(int col);
#endif
