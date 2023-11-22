#ifndef Included_utils_h
#define Included_utils_h
#define KEY_ESC 033
#define KEY_UP 06655501
#define KEY_DN 06655502
#define KEY_LEFT 06655504
#define KEY_RIGHT 06655503
#define KEY_BACKSPACE 0177
#define KEY_INS 03326631176
#define KEY_DEL 03326635576
#define KEY_HOME 06655510
#define KEY_END 06655506
#define KEY_PGUP 03326636576
#define KEY_PGDN 03326637176
#define KEY_CTRL_LEFT 0160163
#define KEY_CTRL_RIGHT 0160164
#define KEY_CTRL_UP 0160215
#define KEY_CTRL_DN 0160221
#define KEY_CTRL_INS 0160222
#define KEY_CTRL_DEL 0160223
#define KEY_CTRL_HOME 0160167
#define KEY_CTRL_END 0160165
#define KEY_CTRL_PGUP 0160206
#define KEY_CTRL_PGDN 0160166
#define KEY_F1 073
#define KEY_F2 074
#define KEY_F3 075
#define KEY_F4 076
#define KEY_F5 077
#define KEY_F6 0100
#define KEY_F7 0101
#define KEY_F8 0102
#define KEY_F9 0103
#define KEY_F10 0104
#define KEY_F11 0160205
#define KEY_F12 0160206
enum basic_colour
{   BLACK = 30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE   };
enum text_decoration
{   BOLD = 1, FAINT, ITALIC, UNDERLINE, STRIKE = 9, OVERLINE = 53   };
enum cursor_direction
{   UP = 'A', DOWN, RIGHT, LEFT   };
typedef
#ifdef _WIN32
long
#endif
long unsigned rand_t;
struct linear_congruential_generator
{
    rand_t slope, yint, mod;
    rand_t seed;
};
typedef long
#ifdef _WIN32
long
#endif
keystroke_t;
keystroke_t keystroke(void);
void *malloc_table(unsigned width, unsigned height, unsigned size);
void *tableset(void *ptr, int ch, unsigned width, unsigned height, unsigned size);
#ifdef _WIN32
long
#endif
long timems(void);
int lcg_next(struct linear_congruential_generator *gen);
void init_lcg_default(struct linear_congruential_generator *gen);
void init_lcg(struct linear_congruential_generator *gen, rand_t slope, rand_t yint, rand_t mod, rand_t seed);
int stdincnt(void);
int thsleep(unsigned ms);
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
