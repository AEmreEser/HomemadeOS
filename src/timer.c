#include "include/typedefs.h" // stack frame type
#include "include/isr_irq/irq.h"
#include "include/utils/vga_utils.h"
#include "include/utils/system_utils.h" // for outportb() 

#include "include/timer/timer.h"

#define PIT_CHANNEL0 0x40
#define PIT_COMMAND  0x43
#define PIT_FREQ     1193182
#define PIT_IRQ_HZ   100 // fire 100 times per second

int uptime_counter = 0; // counts total number of ticks

void pit_init(void) {
    uint16_t divisor = PIT_FREQ / PIT_IRQ_HZ;

    // channel 0, access mode lobyte/hibyte, mode 3 (square wave)
    outportb(PIT_COMMAND, 0x36);

    outportb(PIT_CHANNEL0, (uint8_t)(divisor & 0xFF));

    outportb(PIT_CHANNEL0, (uint8_t)((divisor >> 8) & 0xFF));
}


void timer_int_handler(int_stack_frame_t * sf){
    uptime_counter++;

    static int secs = 0;

    if (uptime_counter % 18 == 0){
        offset = clear();
        offset = print_str("Seconds = ", CL_GREEN_ON_BLACK, offset);
        offset = print_num((uint8_t) secs++, CL_WHITE_ON_BLACK, offset);
    }

    outportb(0x20, 0x20); // end of interrupt
}

void install_timer_irq(void){
    install_single_irq(0, timer_int_handler);
    offset = print_str("debug print\n", CL_GREEN_ON_BLACK, offset);
    pit_init();
}

void delay(int duration){
    int until = uptime_counter + duration;
    while (uptime_counter < until);
}