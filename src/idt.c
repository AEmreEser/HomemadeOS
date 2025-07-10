#include "include/idt/idt.h"

IDT_descriptor_t idt_desc;
IDT_entry_t idt[NUM_IDT];

void init_idt_entry(IDT_entry_t * const idt, uint8_t order, uint32_t offset_entry, uint16_t selector_entry, uint8_t attr){
    // 5 primitive moves, implemented this way cause C does not have RVO
    idt[order].attr = attr;
    idt[order].offset_entry_high = ((offset_entry & 0xffff) >> 16);
    idt[order].offset_entry_low = offset_entry & 0xffff;
    idt[order].selector_entry = selector_entry;
    idt[order].RESERVED = 0;
}
