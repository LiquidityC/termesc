#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdio.h>
#include "termesc.h"

#define send(str) write(1,str,sizeof(str))

static struct termdim dim = { 0, 0 };

static void
on_resize(int unused)
{
	(void) unused;

	struct winsize ws;
	ioctl(1, TIOCGWINSZ, &ws);
	dim.rows = ws.ws_row;
	dim.cols = ws.ws_col;
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
	td->rows = dim.rows;
	td->cols = dim.cols;
}

void
termesc_close(void)
{
	// Clean the buffer
	send("\x1b[2J");

	// Switch to normal buffer
	send("\x1b[?1049l");

	termesc_hide_cursor(false);
}
