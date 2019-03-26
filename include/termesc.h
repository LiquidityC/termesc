#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

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

#define esc "\x1b"
#define esca esc "["
#define fmt(str) esca str "m"
#define with ";"

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
termesc_set_scroll(uint32_t start, uint32_t end);

void
termesc_reset_scroll(void);

void
termesc_close(void);
