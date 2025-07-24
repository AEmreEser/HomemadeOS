#ifndef _TIMER_H_
#define _TIMER_H_

extern int uptime_counter; // counts total number of ticks

void timer_int_handler(int_stack_frame_t * sf);

void install_timer_irq(void);

void delay(int duration);

#endif