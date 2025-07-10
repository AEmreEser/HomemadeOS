#include "include/typedefs.h"

#include "include/utils/vga_utils.h"
#include "include/isr/isr.h"
#include "include/utils/system_utils.h"

void kmain(){

    offset_t offset = clear(); 
    enable_cursor();

    offset = print_str_times(12, ENDL_STR, CL_GREEN_ON_BLACK, offset);
    offset = print_str_times(40 - 11, SP_STR, CL_GREEN_ON_BLACK, offset);
    offset = print_str("--BORED & LONELY OS--\n\0", CL_GREEN_ON_BLACK, offset);
    offset = print_str_times(40 - 4, SP_STR, CL_GREEN_ON_BLACK, offset);
    offset = print_str("v 0.3.5\n\0", CL_WHITE_ON_BLACK, offset);
    offset = print_str("\n                       Copyright: Ahmet Emre Eser - 2023 - 2025\n\0", CL_WHITE_ON_BLACK, offset);

    load_isr_32();
    // __asm__ __volatile__("int $2");
    // __asm__ __volatile__("int $3");

	for(;;); // inf loop without leaving kmain()

}

