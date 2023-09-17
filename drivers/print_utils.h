#ifndef _PRINT_UTILS_H_
#define _PRINT_UTILS_H_

#include "crtc_vga_driver.h"
#include "../src/typedefs.h"

offset_t print_str_times(uint8_t times, const char * str, uint8_t attr, offset_t offset){

    for (uint8_t i = 0; i < times; i++){
        offset = print_str(str, attr, offset);
    }

    return set_cursor(offset);
}


    #ifdef DBG
    // fills the screen with A chars
    offset_t print_many_a(offset_t offset){
        
        uint16_t i = 0, j = 0;
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
    #endif


#endif