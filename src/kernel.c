#include "include/typedefs.h"

#include "include/utils/vga_utils.h"
#include "include/isr_irq/isr.h"
#include "include/isr_irq/irq.h"
#include "include/idt/idt.h"
#include "include/utils/system_utils.h"
#include "include/timer/timer.h"
#include "include/kbd/kbd.h"

extern offset_t offset;

void kmain(){

    // offset_t offset = clear(); 
    offset = clear(); 
    enable_cursor();

    offset = print_str_times(12, ENDL_STR, CL_GREEN_ON_BLACK, offset);
    offset = print_str_times(40 - 11, SP_STR, CL_GREEN_ON_BLACK, offset);
    offset = print_str("--BORED & LONELY OS--\n\0", CL_GREEN_ON_BLACK, offset);
    offset = print_str_times(40 - 4, SP_STR, CL_GREEN_ON_BLACK, offset);
    offset = print_str("v 0.3.6\n\0", CL_WHITE_ON_BLACK, offset);
    offset = print_str("\n                       Copyright: Ahmet Emre Eser - 2023 - 2025\n\0", CL_WHITE_ON_BLACK, offset);

    install_idt();
    install_irq();
    install_timer_irq();
    install_kbd_irq();

    int_enable();

    delay(500);
    offset = clear();
    enable_cursor();

    // volatile char a = 32 / 0;
    // offset = print_num(a, CL_GREEN_ON_BLACK, offset);

	for(;;); // inf loop without leaving kmain()

}

