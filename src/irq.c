#include "include/isr_irq/irq.h"
#include "include/idt/idt.h"
#include "include/utils/system_utils.h" // for outportb() 

// this file borrows a lot from brandon's tutorial
// we have to comply with weird 90s chip opcodes and its abi so there's not much
// room for creativity here

// custom irq routines go here
void * irq_handler_array[NUM_IRQ];

void install_single_irq(int num_irq, void (* handler)(int_stack_frame_t * sf)){
    irq_handler_array[num_irq] = handler;
}

void remove_single_irq(int num_irq){
    irq_handler_array[num_irq] = 0;
}

// this is mostly taken from brandon's tutorial (because I don't want to read the manuals for 90s PIC chips)
// but the comments are mine : ) - so I did end up reading the manual (only as much as needed)
void remap_irq(void)
{
    // 0x20 Master irq controller chip port
    // 0xA0 slave irq controller chip port
    // 0x11 initialization command
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    // we offset the irqs by 32 and 40 respectively
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    // tell master that there is a slave pic
    outportb(0x21, 0x04);
    // tell the slave its identity (mask)
    outportb(0xA1, 0x02);
    // set PICs to 8086 mode
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    // unmask/enable all interrupts
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

void install_irq(){
    remap_irq();

    init_idt_entry(idt, 32,  (uint32_t) irq0,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 33,  (uint32_t) irq1,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 34,  (uint32_t) irq2,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 35,  (uint32_t) irq3,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 36,  (uint32_t) irq4,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 37,  (uint32_t) irq5,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 38,  (uint32_t) irq6,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 39,  (uint32_t) irq7,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 40,  (uint32_t) irq8,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 41,  (uint32_t) irq9,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 42,  (uint32_t) irq10,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 43,  (uint32_t) irq11,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 44,  (uint32_t) irq12,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 45,  (uint32_t) irq13,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 46,  (uint32_t) irq14,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 47,  (uint32_t) irq15,  SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);

    __asm__ __volatile__ ("sti"); // officially enable interrupts
}

void irq_handler(int_stack_frame_t * sf){

    // ie. if the handler exists inside the array
    void (* handler)(int_stack_frame_t * sf) = irq_handler_array[sf->intr_number - 32];
    if (irq_handler_array[sf->intr_number - 32] != 0) {
       handler(sf); 
    }

    // need to send an end of interrupt command to the slave controller if the irq
    // was raisd by it
    if (sf->intr_number >= 40)
    {
        outportb(0xA0, 0x20);
    }

    // need to sned this to the master since we get all irqs from it
    outportb(0x20, 0x20);
}
