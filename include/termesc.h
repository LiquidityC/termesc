#pragma once

/**
 * @file termesc.h
 * @author Linus Probert <linus.probert@gmail.com>
 * @brief The main termesc header
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

/**
 * @defgroup Attributes
 *
 * @{
 */
/** Reset output */
#define     plain "0"
/** no */
#define        no "2"
/** bright output */
#define    bright "1"
/** dim output */
#define       dim "2"
/** italic output */
#define    italic "3"
/** underline output */
#define underline "4"
/** reverse colors of output */
#define   reverse "7"

/** foreground attribute @see fmt */
#define        fg "3"
/** background attribute @see fmt */
#define        bg "4"
/** bright foreground attribute @see fmt */
#define     br_fg "9"
/** bright background attribute @see fmt */
#define     br_bg "10"
/** black color */
#define     black "0"
/** red color */
#define       red "1"
/** green color */
#define     green "2"
/** yellow color */
#define    yellow "3"
/** blue color */
#define      blue "4"
/** magenta color */
#define   magenta "5"
/** cyan color */
#define      cyan "6"
/** white color */
#define     white "7"

/** escape char */
#define esc "\x1b"
/** escape char with delimiter */
#define esca esc "["
/** with to be used when combing attributes @see fmt */
#define with ";"
/** @} */

/**
 * @def fmt(str)
 * The main formating macro.
 *
 * To be used in combination with printing and the attribute macros.
 *
 * @code{.c}
 * // Example:
 * printf(fmt(fg red with underline) "The meaning of life is: %d" fmt(plain), 42);
 * @endcode
 *
 * @param str The attributes you want to set
 */
#define fmt(str) esca str "m"

/**
 * A struct describing the terminals dimensions
 */
struct termdim {
	/** Row count */
	uint32_t rows;
	/** Col count */
	uint32_t cols;
};

/**
 * Initiates termesc.
 *
 * Essentially this switches to the alternate buffer and clears it in
 * preparation for your input. You can omit this step and do it manually
 * using the ansi escape sequences if you want.
 */
void
termesc_init(void);
 
/**
 * Toggle cursor visibility.
 *
 * @param hide true or false
 */
void
termesc_hide_cursor(bool hide);

/**
 * Populate a termdim struct with the current terminal dimensions.
 *
 * @param td pointer to a termdim struct
 */
void
termesc_get_dimensions(struct termdim *td);

/**
 * Move the cursor to a particular row and column.
 *
 * @param col The column you want
 * @param row The row you want
 */
void
termesc_goto(uint32_t col, uint32_t row);

/**
 * Define a scrolling area.
 *
 * @param start The start row of the scrolling region
 * @param end The end row of the scrolling region
 */
void
termesc_set_scroll(uint32_t start, uint32_t end);

/**
 * Reset scrolling region to the entire terminal
 */
void
termesc_reset_scroll(void);

/**
 * Reset the terminal to it's original state.
 *
 * If you want to provide a good user experience you should be to sure to make
 * this call in all scenarios where your application shuts down. This should
 * probably include signal SIGINT and SIGHUP handlers.
 */
void
termesc_close(void);
