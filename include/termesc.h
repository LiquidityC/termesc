#pragma once

#include <stdbool.h>

struct termdim {
	unsigned int rows;
	unsigned int cols;
};

void
termesc_init(void);

void
termesc_hide_cursor(bool hide);

void
termesc_get_dimensions(struct termdim *);

void
termesc_close(void);
