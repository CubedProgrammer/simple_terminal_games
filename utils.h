#ifndef Included_utils_h
#define Included_utils_h
#define KEY_ESC 033
#define KEY_UP 06655501
#define KEY_DN 06655502
#define KEY_LEFT 06655504
#define KEY_RIGHT 06655503
#define KEY_BACKSPACE 0177
#define KEY_DEL 03326635576
#define KEY_HOME 06655510
#define KEY_END 06655506
#define KEY_PGUP 03326636576
#define KEY_PGDN 03326637176
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
void *malloc_table(unsigned width, unsigned height, unsigned size);
void *tableset(void *ptr, int ch, unsigned width, unsigned height, unsigned size);
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
