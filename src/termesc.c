#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdio.h>
#include <stdarg.h>
#include <termios.h>
#include "termesc.h"

#define     plain "0"
#define        no "2"
#define    bright "1"
#define       dim "2"
#define    italic "3"
#define underline "4"
#define   reverse "7"

#define        fg "3"
#define        bg "4"
#define     br_fg "9"
#define     br_bg "10"
#define     black "0"
#define       red "1"
#define     green "2"
#define    yellow "3"
#define      blue "4"
#define   magenta "5"
#define      cyan "6"
#define     white "7"

#define    alt_buf "?1049"
#define       curs "?25"
#define term_clear "2J"
#define clear_line "2K"
#define       high "h"
#define        low "l"
#define       jump "H"

#define esc "\x1b"
#define esca esc "["
#define fmt(str) esca str "m"
#define with ";"
#define jump "H"
#define send(str) write(1, str, sizeof(str))

static struct termdim dimension = { 0, 0 };
static struct termios initial;

static void
fmtsend(const char *fmt, ...)
{
	va_list args;
	char msg[1024];
	va_start(args, fmt);
	vsnprintf(msg, 1024, fmt, args);
	send(msg);
}

static void
on_resize(int unused)
{
	(void) unused;

	struct winsize ws;
	ioctl(1, TIOCGWINSZ, &ws);
	dimension.rows = ws.ws_row;
	dimension.cols = ws.ws_col;
}

static void
clear_buffer(void)
{
	send("\x1b[2J");
}

void
termesc_init(void)
{
	//enter the alternate buffer
	send("\x1b[?1049h");

	// Termios init
	struct termios t;
	tcgetattr(1, &t);
	initial = t;
	t.c_lflag &= (~ECHO & ~ICANON);
	tcsetattr(1, TCSANOW, &t);

	//clean up the buffer
	clear_buffer();

	// Get the initial rows and cols
	on_resize(0);
}

void
termesc_hide_cursor(bool hide)
{
	if (hide)
		send("\x1b[?25l");
	else
		send("\x1b[?25h");
}

void
termesc_get_dimensions(struct termdim *td)
{
	td->rows = dimension.rows;
	td->cols = dimension.cols;
}

void
termesc_goto(uint32_t col, uint32_t row)
{
	printf(esca "%u" with "%u" jump, row, col);
}

void
termesc_close(void)
{
	// Clean the buffer
	send("\x1b[2J");

	// Switch to normal buffer
	send("\x1b[?1049l");

	termesc_hide_cursor(false);

	// Termios restore
	tcsetattr(1, TCSANOW, &initial);
}
