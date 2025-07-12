#include "include/idt/idt.h"
#include "include/isr_irq/isr.h" // load_isr_32()
#include "include/utils/system_utils.h"

IDT_descriptor_t idt_desc;
IDT_entry_t idt[NUM_IDT];

void init_idt_entry(IDT_entry_t * const idt, uint8_t order, uint32_t offset_entry, uint16_t selector_entry, uint8_t attr){
    // 5 primitive moves, implemented this way cause C does not have RVO
    idt[order].attr = attr;
    idt[order].offset_entry_high = ((offset_entry >> 16) & 0xffff) ;
    idt[order].offset_entry_low = offset_entry & 0xffff;
    idt[order].selector_entry = selector_entry;
    idt[order].RESERVED = 0;
}


void install_idt(){
    memset( (unsigned char *) (idt), 0, (NUM_IDT * sizeof(IDT_entry_t)) );

    load_isr_32();

    idt_desc.idt_base = (uint32_t) (idt);
    idt_desc.idt_limit = ( (NUM_IDT * sizeof(IDT_entry_t)) - 1);
    //                      256 * 64 bits - 1 = 0x7ff

    load_idt(&idt_desc);
}