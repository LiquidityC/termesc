#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdio.h>
#include <stdarg.h>
#include <termios.h>

#include "termesc.h"

#define    alt_buf "?1049"
#define       curs "?25"
#define term_clear "2J"
#define clear_line "2K"
#define       high "h"
#define        low "l"
#define       jump "H"
#define     scroll "r"

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

	// Listen for resize signals
	signal(SIGWINCH, on_resize);
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
termesc_set_scroll(uint32_t start, uint32_t end)
{
	printf(esca "%u" with "%u" scroll, start, end);
}

void
termesc_reset_scroll(void)
{
	printf(esca scroll);
}

void
termesc_close(void)
{
	termesc_reset_scroll();

	// Clean the buffer
	send("\x1b[2J");

	// Switch to normal buffer
	send("\x1b[?1049l");

	termesc_hide_cursor(false);

	// Termios restore
	tcsetattr(1, TCSANOW, &initial);
}
