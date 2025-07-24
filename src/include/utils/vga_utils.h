#ifndef _VGA_UTILS_H_
#define _VGA_UTILS_H_

/* NOTES: 
    USING VGA
    VIDEO MEMORY ORGANIZATION: 16 bits per letter: low byte char, high byte attribute/formatting info
*/

// VIDEO DEFINITIONS
#define WIDTH 80 // COLUMNS #
#define HEIGHT 25 // ROWS #
#define NUM_CHARS (WIDTH * HEIGHT)
#define MAX_OFFSET ((WIDTH - 1) * (HEIGHT - 1) * (2))
#define VID_MEM_ADDR 0xb8000 // vga text buffer address
#define CL_GREEN_ON_BLACK 0x02
#define CL_WHITE_ON_BLACK 0x0f

#define ENDL_CH '\n'
#define ENDL_STR "\n"
#define SP_CH ' '
#define SP_STR " \0"

#define CRTC_REG_DATA 0x3D5
#define CRTC_REG_ADDR 0x3D4

typedef uint16_t offset_t;
typedef uint8_t dim_t; // dimension types

extern offset_t offset;

extern unsigned char * const VID_MEM_PTR; //  = (unsigned char *) (VID_MEM_ADDR);

offset_t calculate_offset(dim_t row, dim_t col);

offset_t get_cursor_offset(void);

void enable_cursor(void);

void disable_cursor(void);

offset_t set_cursor(const offset_t offset);

offset_t scroll_line(const unsigned short lines);

offset_t adjust_screen(offset_t offset);

// UTILITY FUNCTION, DOES NOT SET THE CURSOR TO THE END OF THE CURRENT CHARACTER
offset_t util_print_chr(const dim_t ch, uint8_t attr, offset_t offset);

// SETS CURSOR TO THE NEW CHAR'S POSITION
offset_t print_single_chr(const dim_t ch, unsigned char attr, offset_t offset);

// ALWAYS RETURNS 0 -- leftmost corner offset
offset_t clear(void);

offset_t clear_line(dim_t line);

offset_t clear_current_line(void);

// SETS CURSOR TO END OF STR
offset_t print_str(const char * str, char attr, offset_t offset);

// SET OFFSET TO END OF NUM
offset_t print_num(uint8_t num, char attr, offset_t offset);

offset_t print_str_times(uint8_t times, const char * str, uint8_t attr, offset_t offset);

char get_att(unsigned char foregnd, unsigned char backgnd);

#ifdef DBG
offset_t print_chr_coord(const unsigned char ch,unsigned char attr, dim_t row, dim_t col);

offset_t print_single_chr_coord(const unsigned char ch, unsigned char attr, dim_t row, dim_t col);
#endif


#endif