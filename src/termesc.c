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
static struct termios termios_initial, termios_modified;

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
	send(esca term_clear);
}

void
termesc_init(void)
{
	//enter the alternate buffer
	send(esca alt_buf high);

	// Termios retrieval
	tcgetattr(1, &termios_modified);
	termios_initial = termios_modified;

	//clean up the buffer
	clear_buffer();

	// Get the initial rows and cols
	on_resize(0);

	// Listen for resize signals
	signal(SIGWINCH, on_resize);
}

void
termesc_disable_echo_canonical(void)
{
	termios_modified.c_lflag &= (~ECHO & ~ICANON);
	tcsetattr(1, TCSANOW, &termios_modified);
}

void
termesc_hide_cursor(bool hide)
{
	if (hide)
		send(esca curs low);
	else
		send(esca curs high);
}

void
termesc_clear_term(void)
{
	clear_buffer();
}

void
termesc_clear_line(void)
{
	send(esca clear_line);
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
	// Termios restore
	tcsetattr(1, TCSANOW, &termios_initial);

	// Clean the buffer
	clear_buffer();

	termesc_hide_cursor(false);

	// Switch to normal buffer
	send(esca alt_buf low);
}
