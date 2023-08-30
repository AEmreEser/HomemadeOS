#define DBG

#include "../drivers/crtc_vga_driver.h"

void kmain(){

    const volatile char * test_str = "This is a test!\0";
    print_str_vid_mem(test_str);

    // print_single_chr_coord('A', CL_GREEN_ON_BLACK, 0, 0);

    enable_cursor();
    // set_cursor(calculate_offset(0,0));

    short i = 0, j = 0;
    offset_t offset = calculate_offset(j, i);

    for ( j = 0; j < HEIGHT; j++) {
        for ( i = 0; i < WIDTH; i++){
            
            if (i != 10 || j != 10) {
                offset = print_single_chr('A', CL_GREEN_ON_BLACK, offset);
            }
            else { // TO DO: print_chr must return the offset for the next character --> else we cannot handle \n fast
                    // print string will simply be a while loop that checks for valid offset values
                i = -1;
                j++;
                offset = print_single_chr('\n', CL_GREEN_ON_BLACK, offset);
            }
        }
    }

    // TESTING:
    offset = print_single_chr('x', CL_GREEN_ON_BLACK, offset);
    offset = print_single_chr('\n', CL_GREEN_ON_BLACK, offset);

    // offset = clear(); // offset 0

    offset = print_str("this is a test\n\0", CL_GREEN_ON_BLACK, offset);
    offset = print_str("\n\0", CL_GREEN_ON_BLACK, offset);

    // offset = print_single_chr('x', CL_GREEN_ON_BLACK, offset);
    // offset = print_single_chr('x', CL_GREEN_ON_BLACK, offset);
    // offset = print_single_chr('\n', CL_GREEN_ON_BLACK, offset);
    // offset = print_single_chr('x', CL_GREEN_ON_BLACK, offset);

}

