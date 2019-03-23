#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "termesc.h"

int main(int argc, char *argv[])
{
	termesc_init();
	termesc_hide_cursor(true);
	sleep(5);
	termesc_close();
}
