#ifndef _CRTC_VGA_DRIVERS_H_
#define _CRTC_VGA_DRIVERS_H_

/* NOTES: 
    USING VGA
    VIDEO MEMORY ORGANIZATION: 16 bits per letter: low byte char, high byte attribute/formatting info
*/

extern unsigned char volatile inline read_byte(const unsigned int port);
extern unsigned short volatile inline read_word(const unsigned int port);
extern unsigned int volatile inline read_dbl_word(const unsigned int port);
extern void volatile inline write_byte(const unsigned int port, const unsigned char data);
extern void volatile inline write_word(const unsigned int port, const unsigned short data);
extern void volatile inline write_dbl_word(const unsigned int port, const unsigned int data);

#include "port_utils.h"

// VIDEO DEFINITIONS
#define WIDTH 80 // COLUMNS #
#define HEIGHT 25 // ROWS #
#define NUM_CHARS (WIDTH * HEIGHT)
#define MAX_OFFSET ((WIDTH - 1) * (HEIGHT - 1) * (2))
#define VID_MEM_ADDR 0xb8000 // vga text buffer address
#define CL_GREEN_ON_BLACK 0x02
#define CL_WHITE_ON_BLACK 0x0f

#define ENDL_CH '\n'
#define ENDL_STR "\n\0"
#define SP_CH ' '
#define SP_STR " \0"

#define CRTC_REG_DATA 0x3D5
#define CRTC_REG_ADDR 0x3D4

typedef unsigned short offset_t;
typedef unsigned char dim_t; // dimension types

unsigned char * const VID_MEM_PTR = (unsigned char *) (VID_MEM_ADDR);

offset_t calculate_offset(dim_t row, dim_t col){
    // RETURNS THE OFFSET IN # OF CHARACTER SLOTS IN VID MEM - NOT NUMBER OF CHARS ON THE SCREEN
    return 2 * ( row * WIDTH + col ); // 2 bytes each char+attr slot in vid mem
}
offset_t get_cursor_offset(void){
    // ASSUMING ONE CHAR SIZED CURSOR
    // RETURNS THE OFFSET IN # OF CHARACTER SLOTS IN VID MEM - NOT NUMBER OF CHARS ON THE SCREEN
    // offset = number of char slots from the top left to specified position -> hence byte address in memory should be 2 times the offset since vid mem is addressed by bytes
    write_byte(CRTC_REG_ADDR, 0x0E); // select index for cursor location high
    offset_t reg_val = read_word(CRTC_REG_DATA);
    reg_val <<= 8;

    write_byte(CRTC_REG_ADDR, 0x0F); // select index for cursor location low
    reg_val |= read_word(CRTC_REG_DATA); 
    return reg_val << 1; // * 2
}

void enable_cursor(void){
    // DOES NOT MODIFY THE LOCATION OF THE CURSOR, CURSOR LOCATION SHOULD BE ADJUSTED BEFORE USE
    write_byte(CRTC_REG_ADDR, 0x0A); // select index for cursow row scan start reg
    unsigned char reg_val = read_byte(CRTC_REG_DATA);
    write_byte(CRTC_REG_DATA, reg_val & (0xdf)); // clear bit 5 = enables cursor (active low)

    write_byte(CRTC_REG_ADDR, 0x0B); // cursor end reg
    reg_val = read_byte(CRTC_REG_DATA);
    write_byte(CRTC_REG_DATA, reg_val & 0xef); // set bit 5 = disable cursor
}

void disable_cursor(void){
    // DOES NOT MODIFY THE LOCATION FO THE CURSOR
    write_byte(CRTC_REG_ADDR, 0x0A); // cursor start reg
    unsigned char reg_val = read_byte(CRTC_REG_DATA);
    write_byte(CRTC_REG_DATA, reg_val & 0xef); // set bit 5 = disable cursor
}

offset_t set_cursor(const offset_t offset){
    offset_t off = offset / 2; // vid mem offset to char # offset
    write_byte(CRTC_REG_ADDR, 0x0E); // cursor location high == offset high byte
    write_byte(CRTC_REG_DATA, (off & 0xff00) >> 8); 

    write_byte(CRTC_REG_ADDR, 0x0F); // cursor location low == offset low byte
    write_byte(CRTC_REG_DATA, off & 0x00ff);

    return offset;
}

offset_t scroll_line(const unsigned short lines){ 

    unsigned short addr_difference = WIDTH * 2 * lines;

    for (unsigned short i = 0; i < (( HEIGHT - lines) * WIDTH); i++){ // i: char count
        VID_MEM_PTR[i * 2] = VID_MEM_PTR[i * 2 + addr_difference];
        VID_MEM_PTR[i * 2 + 1] = VID_MEM_PTR[i * 2 + 1 + addr_difference];
    }
    offset_t offset;
    for (unsigned short i = 0; i < lines * WIDTH; i++){ // clear last <lines> many rows
        offset = (i + (( HEIGHT - lines) * WIDTH)) * 2;
        VID_MEM_PTR[offset] = 0x00;
        VID_MEM_PTR[offset + 1] = 0x00;
    }

    return calculate_offset((HEIGHT - lines), 0);

}

offset_t adjust_screen(offset_t offset){
    // returns the new location of the cursor after scrolling
    dim_t cursor_row = ((offset / 2) / WIDTH);
    dim_t cursor_col = ((offset / 2) % WIDTH);
    offset_t new_offset;

    if (cursor_row >= HEIGHT && cursor_col >= WIDTH){ // last character slot
        new_offset = scroll_line(1);
        // new_offset = calculate_offset(cursor_row - 1, 0);
    }
    else if (cursor_row >= HEIGHT){
        new_offset = scroll_line(1);
        // new_offset = calculate_offset(cursor_row - 1, cursor_col);
    }
    else if (cursor_col >= WIDTH){
        new_offset = calculate_offset(cursor_row + 1, 0);
    }
    else {
        new_offset = calculate_offset(cursor_row, cursor_col);
    }

    return new_offset;
}

// UTILITY FUNCTION, DOES NOT SET THE CURSOR TO THE END OF THE CURRENT CHARACTER
offset_t print_chr(const dim_t ch, unsigned char attr, offset_t offset){
    // provide any value < 0 for row or column to use the deafult address of the cursor
    if (attr < 0){
        attr = CL_WHITE_ON_BLACK;
    }

    dim_t cursor_row = (dim_t) (offset / (WIDTH * 2));
    // unsigned char cursor_col = offset % (WIDTH * 2);

    if (ch != '\n'){
        VID_MEM_PTR[offset] = ch;
        VID_MEM_PTR[offset + 1] = attr;
        offset += 2;
        offset = adjust_screen(offset); 
    }
    else {

        if (offset >= calculate_offset(24, 0)){ // newline received at the last line
            offset = scroll_line(1);
        }
        else {
            offset = calculate_offset(cursor_row + 1, 0); // move cursor to beg of next line
        }
    }

    return offset;
}

// SETS CURSOR TO THE NEW CHAR'S POSITION
offset_t print_single_chr(const dim_t ch, unsigned char attr, offset_t offset){
    return set_cursor(print_chr(ch, attr, offset));
}

// ALWAYS RETURNS 0
offset_t clear(void){

    offset_t index_offset = 0;

    for (dim_t i = 0; i < HEIGHT; i++){
        for (dim_t j = 0; j < WIDTH; j++){
            VID_MEM_PTR[index_offset] = 0;
            VID_MEM_PTR[index_offset + 1] = 0;
            index_offset += 2;
        }
    }

    set_cursor(0);
    return 0;
}

// SETS CURSOR TO END OF STR
offset_t print_str(const char * str, char attr, offset_t offset){
    unsigned short i = 0; // len = 0;
    unsigned char ch = str[i];
    while (ch != 0){
        offset = print_chr(ch, attr, offset);
        // len++;
        ch = str[++i];
    }

    return set_cursor(offset);
}




#ifdef DBG
offset_t print_chr_coord(const unsigned char ch,unsigned char attr, dim_t row, dim_t col){
    return print_chr(ch, attr, calculate_offset(row,col));
}

offset_t print_single_chr_coord(const unsigned char ch, unsigned char attr, dim_t row, dim_t col){
    return set_cursor(print_chr(ch, attr, calculate_offset(row, col)));
}
#endif


#endif