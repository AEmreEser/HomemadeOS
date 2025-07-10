#ifndef _IDT_H_
#define _IDT_H_

#include "../typedefs.h"

typedef struct __attribute__((packed)) {
// 32 bit mode: little endian high word: offset, low byte: size 

    uint8_t size_idt; // ONE LESS than size(idt) - 255
    uint16_t offset_idt; // linear address of the idt

} IDT_descriptor_t; // loaded intor idt register

typedef struct __attribute__((packed)) {
    // each entry: 8 bytes long (IA-32 only)

    uint16_t offset_entry_low; // address of the ISR entry point
    uint16_t selector_entry; // segment selector - kernel code segment in gdt

    uint8_t RESERVED; // always 0
    
    uint8_t attr; /* attr:
                    <3..0>: gate type
                    <4>: always 0
                    <6..5>: cpu privilege levels for interrupt
                    <7>: present bit, 1 if entry is valid: means we have an isr for this interrupt present, else we get an 'unhandled interrupt' exception
                    */
    uint16_t offset_entry_high; // offset entry split into two

} IDT_entry_t;

#define ATTR_INT_GATE_32 0x8E // present: 1, priv: 00, always 0 bit,  type 1110/32 bit int gate
#define ATTR_TRAP_GATE_32 0x8F // present: 1, priv: 00, always 0 bit,  type 1111/32 bit trap gate
#define SELECTOR_KERNEL_CODE_SEGMENT 0x08
#define NUM_IDT 256

// IDT DECLARATIONS:
extern IDT_descriptor_t idt_desc;
extern IDT_entry_t idt[NUM_IDT];

// initializes idt[order] with the provided parameters
void init_idt_entry(IDT_entry_t * const idt, uint8_t order, uint32_t offset_entry, uint16_t selector_entry, uint8_t attr);

void inline volatile load_idt(const IDT_descriptor_t * const desc) {
    __asm__ volatile("lidt %%eax" : : "a" (desc) );
}


#endif