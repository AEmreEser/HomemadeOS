#include "../drivers/crtc_vga_driver.h"

void kmain(){

    const volatile char const * test_str = "This is a test!\0";
    print_str_vid_mem(test_str);

    print_chr('A', CL_GREEN_ON_BLACK, 0, 0);

    enable_cursor();
    set_cursor(calculate_offset(0,1));

    short i = 0, j = 0;
    for ( j = 0; j < HEIGHT; j++) {
        for ( i = 0; i < WIDTH; i++){
            
            if (i != 10 || j != 10) {
                print_chr('A', CL_GREEN_ON_BLACK, j, i);
            }
            else { // TO DO: print_chr must return the offset for the next character --> else we cannot handle \n fast
                    // print string will simply be a while loop that checks for valid offset values
                j++; // skip a row
                i = -1;
                print_chr('\n', CL_GREEN_ON_BLACK, j, i);
            }
        }
    }

    print_chr('A', CL_GREEN_ON_BLACK, 24, 79); // automatic scroll works
    print_chr('A', CL_GREEN_ON_BLACK, 24, 0); // automatic scroll works
}

