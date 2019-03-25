#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

struct termdim {
	uint32_t rows;
	uint32_t cols;
};

void
termesc_init(void);

void
termesc_hide_cursor(bool hide);

void
termesc_get_dimensions(struct termdim *);

void
termesc_goto(uint32_t col, uint32_t row);

void
termesc_close(void);
