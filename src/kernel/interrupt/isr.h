#ifndef _INT_HANDLER_H_
#define _INT_HANDLER_H_

#include "../../typedefs.h"
#include "../../../drivers/print_utils.h"
#include "idt.h"

// taken from http://www.osdever.net/bkerndev/index.php
const char *intr_msg[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "Protection Fault - General",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void int_handler(int_stack_frame_t sf){

    if (sf.intr_number < 32) {
        offset_t offset = ("interrupt: ", CL_GREEN_ON_BLACK, clear()); //. clears screen and prints interrupt details
        uint8_t int_num = sf.intr_number;

        offset = print_num(int_num, CL_WHITE_ON_BLACK, offset);
        offset = print_chr(ENDL_CH, CL_GREEN_ON_BLACK, offset);

        offset = print_str(intr_msg[int_num], CL_GREEN_ON_BLACK, offset);
    }

}

// initializes idt[order] with the provided parameters
void init_idt_entry(IDT_entry_t * const idt, uint8_t order, uint32_t offset_entry, uint16_t selector_entry, uint8_t attr){
    // 5 primitive moves, implemented this way cause C does not have RVO
    idt[order].attr = attr;
    idt[order].offset_entry_high = ((offset_entry & 0xff00) >> 16);
    idt[order].offset_entry_low = offset_entry & 0xff;
    idt[order].selector_entry = selector_entry;
    idt[order].RESERVED = 0;
}

void inline volatile load_idt(const IDT_descriptor_t * const desc) {
    __asm__ volatile("lidt %%eax" : : "a" (desc) );
}

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void load_isr_32(){
    init_idt_entry(idt, 0, (uint32_t) isr0, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 1, (uint32_t) isr1, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 2, (uint32_t) isr2, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 3, (uint32_t) isr3, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 4, (uint32_t) isr4, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 5, (uint32_t) isr5, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 6, (uint32_t) isr6, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 7, (uint32_t) isr7, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 8, (uint32_t) isr8, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 9, (uint32_t) isr9, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 10, (uint32_t) isr10, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 11, (uint32_t) isr11, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 12, (uint32_t) isr12, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 13, (uint32_t) isr13, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 14, (uint32_t) isr14, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 15, (uint32_t) isr15, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 16, (uint32_t) isr16, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 17, (uint32_t) isr17, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 18, (uint32_t) isr18, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 19, (uint32_t) isr19, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 20, (uint32_t) isr20, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 21, (uint32_t) isr21, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 22, (uint32_t) isr22, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 23, (uint32_t) isr23, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 24, (uint32_t) isr24, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 25, (uint32_t) isr25, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 26, (uint32_t) isr26, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 27, (uint32_t) isr27, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 28, (uint32_t) isr28, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 29, (uint32_t) isr29, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 30, (uint32_t) isr30, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);
    init_idt_entry(idt, 31, (uint32_t) isr31, SELECTOR_KERNEL_CODE_SEGMENT, ATTR_INT_GATE_32);

}

#endif