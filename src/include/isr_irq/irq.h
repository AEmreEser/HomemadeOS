#ifndef _IRQ_H_
#define _IRQ_H_

#include "../typedefs.h"

#define NUM_IRQ

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

// WARNING: won't do any bounds checks etc. 
// you have to ensure yourself that param num_irq < NUM_IRQ
void install_single_irq(int num_irq, void (* handler)(int_stack_frame_t * sf));

// WARNING: won't do any bounds checks etc. 
// you have to ensure yourself that param num_irq < NUM_IRQ
void remove_single_irq(int num_irq);

void remap_irq(void);

void install_irq();

void int_enable(void);

void irq_handler(int_stack_frame_t * sf);

#endif