#ifndef _CRTC_VGA_DRIVERS_H_
#define _CRTC_VGA_DRIVERS_H_

/* NOTES: 
    USING VGA
    VIDEO MEMORY ORGANIZATION: 16 bits per letter: low nibble char, high nibble attribute/formatting info
*/

#define WIDTH 80 // COLUMNS #
#define HEIGHT 25 // ROWS #
#define VID_MEM_ADDR 0xb8000 // vga text buffer address
#define CL_GREEN_ON_BLACK 0x02
#define CL_WHITE_ON_BLACK 0x0f

#define CRTC_REG_DATA 0x3D5
#define CRTC_REG_ADDR 0x3D4

#include "port_utils.h"

char * const VID_MEM_PTR = (char *) (VID_MEM_ADDR);

// no location specification
volatile void print_str_vid_mem(const volatile char const * str){
// str should be zero terminated

    volatile char ch_iter = *(str);
    volatile char i = (char) (0);

    while (ch_iter != '\0'){
        *((volatile char *) (VID_MEM_PTR + i * 2)) = ch_iter;
        *((volatile char *) (VID_MEM_PTR + i * 2 + 1)) = CL_GREEN_ON_BLACK; 
        i++;
        ch_iter = *(str + i * sizeof(char));
    }

}


short calculate_offset(char row, char col){
    // RETURNS THE OFFSET IN # OF CHARACTER SLOTS IN VID MEM - NOT NUMBER OF CHARS ON THE SCREEN
    return 2 * ( row * WIDTH + col ); // 2 bytes each char+attr slot in vid mem
}

short get_cursor_offset(void){
    // ASSUMING ONE CHAR SIZED CURSOR
    // RETURNS THE OFFSET IN # OF CHARACTER SLOTS IN VID MEM - NOT NUMBER OF CHARS ON THE SCREEN
    // offset = number of char slots from the top left to specified position -> hence byte address in memory should be 2 times the offset since vid mem is addressed by bytes
    write_byte(CRTC_REG_ADDR, 0x0E); // select index for cursor location high
    short reg_val = read_word(CRTC_REG_DATA);
    reg_val <<= 8;

    write_byte(CRTC_REG_ADDR, 0x0F); // select index for cursor location low
    reg_val |= read_word(CRTC_REG_DATA); 
    return reg_val << 1; // * 2
}

void enable_cursor(void){
    // DOES NOT MODIFY THE LOCATION OF THE CURSOR, CURSOR LOCATION SHOULD BE ADJUSTED BEFORE USE
    write_byte(CRTC_REG_ADDR, 0x0A); // select index for cursow row scan start reg
    char reg_val = read_byte(CRTC_REG_DATA);
    write_byte(CRTC_REG_DATA, reg_val & (0xdf)); // clear bit 5 = enables cursor (active low)

    write_byte(CRTC_REG_ADDR, 0x0B); // cursor end reg
    char reg_val = read_byte(CRTC_REG_DATA);
    write_byte(CRTC_REG_DATA, reg_val & 0xef); // set bit 5 = disable cursor
}

void disable_cursor(void){
    // DOES NOT MODIFY THE LOCATION FO THE CURSOR
    write_byte(CRTC_REG_ADDR, 0x0A); // cursor start reg
    char reg_val = read_byte(CRTC_REG_DATA);
    write_byte(CRTC_REG_DATA, reg_val & 0xef); // set bit 5 = disable cursor
}

void set_cursor(short offset){
    offset = offset / 2; // vid mem offset to char # offset
    write_byte(CRTC_REG_ADDR, 0x0E); // cursor location high == offset high byte
    char reg_val = read_byte(CRTC_REG_DATA);
    write_byte(CRTC_REG_DATA, offset & 0xff00); 

    write_byte(CRTC_REG_ADDR, 0x0F); // cursor location low == offset low byte
    reg_val = read_byte(CRTC_REG_DATA);
    write_byte(CRTC_REG_DATA, offset & 0x00ff);
}

void scroll_line(short lines){ 

    int addr_difference = WIDTH * 2 * lines; // width many 2 byte cells to move up

    for(unsigned char i = 0; i < (( HEIGHT - lines) * WIDTH); i++){ // i: char count
        VID_MEM_PTR[i * 2] = VID_MEM_PTR[i * 2 + addr_difference];
        VID_MEM_PTR[i * 2 + 1] = VID_MEM_PTR[i * 2 + 1 + addr_difference];
    }

    for(unsigned char i = 0; i < lines; i++){ // clear last <lines> many lines
        
    }

}

void scroll_adjust(short offset){



}

void print_chr(const char ch, char row, char col, char color){
    // provide any value < 0 for row or column to use the deafult address of the cursor
    if (color == 0){
        color = CL_WHITE_ON_BLACK;
    }

    short offset = 0;

    if (row >= 0 && col >= 0){
        offset = calculate_offset(row, col);
    }
    else {
        offset = get_cursor_offset(); // cursor location
    }

    if (ch == '\n') {
        offset = calculate_offset(row + 1, 0);
    }
    else { 
        *(VID_MEM_PTR + offset) = ch;
        *(VID_MEM_PTR + offset + 1) = color;
    }

    offset += 2; // next empty vid mem cell
    offset = scroll_adjust(offset);
    set_cursor(offset);
}



#endif