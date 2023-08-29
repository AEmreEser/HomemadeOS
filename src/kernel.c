#include "crtc_vga_driver.h"

void kmain(){

    const volatile char const * test_str = "This is a test!\0";
    print_str_vid_mem(test_str);
}
