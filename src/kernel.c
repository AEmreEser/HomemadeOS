#define DBG

#include "../drivers/crtc_vga_driver.h"

#ifdef DBG
offset_t print_many_a(offset_t offset){
    
    short i = 0, j = 0;
    for ( j = 0; j < HEIGHT; j++) {
        for ( i = 0; i < WIDTH; i++){
            
            if (i != 10 || j != 10) {
                offset = print_single_chr('A', CL_GREEN_ON_BLACK, offset);
            }
            else {
                i = -1;
                j++; // compensate for new line jump
                offset = print_single_chr('\n', CL_GREEN_ON_BLACK, offset);
            }
        }
    }
    return offset;
}

offset_t print_str_times(unsigned char times, const char * str, unsigned char attr, offset_t offset){

    for (unsigned char i = 0; i < times; i++){
        offset = print_str(str, attr, offset);
    }

    return set_cursor(offset);
}
#endif



void kmain(){

    enable_cursor();

    offset_t offset = clear(); 
    // // TESTING:
    // offset = print_single_chr('x', CL_GREEN_ON_BLACK, offset);

    offset = print_str_times(12, ENDL_STR, CL_GREEN_ON_BLACK, offset);
    offset = print_str_times(40 - 11, SP_STR, CL_GREEN_ON_BLACK, offset);
    offset = print_str("--BORED & LONELY OS--\n\0", CL_GREEN_ON_BLACK, offset);
    offset = print_str_times(40 - 4, SP_STR, CL_GREEN_ON_BLACK, offset);
    offset = print_str("v 0.3\n\0", CL_WHITE_ON_BLACK, offset);
    offset = print_str("\n                       Copyright: Ahmet Emre Eser - 2023\n\0", CL_WHITE_ON_BLACK, offset);

    

}

