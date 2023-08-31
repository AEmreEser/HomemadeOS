#ifndef _IDT_H_
#define _IDT_H_


typedef struct __attribute__((packed)) {
// 32 bit mode: little endian high word: offset, low byte: size 

    char size_idt; // ONE LESS than size(idt) - 255
    short offset_idt; // linear address of the idt

} IDT_descriptor_t; // loaded intor idt register



typedef struct __attribute__((packed)) {
    // each entry: 8 bytes long (IA-32 only)

    short offset_entry_low; // address of the ISR entry point
    short selector_entry; // segment selector - code segment in gdt

    char RESERVED; // dalways 0
    
    char attr; 
    /* attr:
        <3..0>: gate type
        <4>: always 0
        <6..5>: cpu privilege levels for interrupt
        <7>: present bit, 1 if entry is valid
    */

    short offset_entry_high; // offset entry split into two

} IDT_entry_t;

#define ATTR_INT_GATE_32 0x8E // present: 1, priv: 00, always 0 bit,  type 1110/32 bit int gate
#define ATTR_TRAP_GATE_32 0x8F // present: 1, priv: 00, always 0 bit,  type 1111/32 bit trap gate



#endif