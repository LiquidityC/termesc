#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "termesc.h"

int main(int argc, char *argv[])
{
	termesc_init();
	termesc_hide_cursor(true);

	struct termdim td;
	termesc_get_dimensions(&td);

	termesc_goto(1, 1);
	printf("Top (1/%u)\n", td.rows);

	unsigned int middleRow = td.rows >> 1;
	termesc_goto(1, middleRow);
	printf("Middle (%u/%u)\n", middleRow, td.rows);
	sleep(5);
	termesc_close();
}
