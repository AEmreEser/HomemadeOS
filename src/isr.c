#include "include/typedefs.h"
#include "include/utils/vga_utils.h"
#include "include/idt/idt.h"

#include "include/isr/isr.h"

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
